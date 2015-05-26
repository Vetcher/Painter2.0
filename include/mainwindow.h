#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class Mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	Mainwindow(QWidget *parent = 0);
	~Mainwindow();

private:
	Ui::MainwindowClass ui;
};

#endif // MAINWINDOW_H
