#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "GlobalStorage.h"
#include "ui_mainwindow.h"
#include "base.h"
#include "qmovie.h"
#include "qbuttongroup.h"


class Mainwindow : public QMainWindow, public IInterface
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent = 0);
	~Mainwindow();

// IInterface functions
	virtual void Draw_Point(uint, double, double, flag, Color);
	virtual void Draw_Segment(uint, double, double, double, double, flag, Color);
	virtual void Draw_Circle(uint, double, double, double, flag, Color);
	virtual void Draw_Line(uint, double, double, double, flag, Color);
	virtual void Write_Constraint(uint, V::TConstraint);
// ------------------------
	void LoadCircleStart();
	void LoadCircleStop();

	void WriteError(const char*, const char*);
public slots:
	void updateSpace();
private:

	// ui variables and functions

	Ui::MainwindowClass ui;
	QMovie* loadcircle;
	QButtonGroup* _toolsbuttons;

	// other blocks

	GlobalStorage _storage;
	void ClearScene();
};

#endif // MAINWINDOW_H
