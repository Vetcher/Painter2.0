#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"
#include "base.h"
#include "qmovie.h"
#define ldoub long double
#define uint unsigned

class Mainwindow : public QMainWindow, public IInterface
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent = 0);
	~Mainwindow();

// IInterface functions
	virtual void Draw_Point(uint, ldoub, ldoub, flag, V::Color);
	virtual void Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, V::Color);
	virtual void Draw_Circle(uint, ldoub, ldoub, ldoub, flag, V::Color);
	virtual void Draw_Line(uint, ldoub, ldoub, ldoub, ldoub, flag, V::Color);
	virtual void Write_Constraint(uint, V::TConstraint);
// ------------------------
	void LoadCircleStart();
	void LoadCircleStop();

	void WriteError(const char*, const char*);

private:
	Ui::MainwindowClass ui;
	QMovie* loadcircle;
};

#undef uint
#undef ldoub

#endif // MAINWINDOW_H
