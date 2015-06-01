#include "mainwindow.h"
#include "qmessagebox.h"
#include "qstring.h"

Mainwindow::Mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	// load user graphics interface
	ui.setupUi(this);
	loadcircle = new QMovie(":/icons/loader.gif");
	loadcircle->setSpeed(200);
	ui.loadBar->setMovie(loadcircle);
	LoadCircleStart();
	WriteError("Error", "Tests on start");
	// other functions
	LoadCircleStop();
}

void Mainwindow::LoadCircleStart()
{
	ui.loadBar->setVisible(true);
	loadcircle->start();
}
void Mainwindow::LoadCircleStop()
{
	loadcircle->stop();
	ui.loadBar->setVisible(false);
}
void Mainwindow::WriteError(const char* shorttext, const char* longtext)
{
	ui.statusFrame->setStyleSheet(QLatin1String("background-color: rgb(202, 81, 0); color: rgb(255, 255, 255);"));
	QMessageBox a(this);
	a.setWindowTitle(" ");
	a.setText(shorttext);
	a.setInformativeText(longtext);
	a.setIcon(QMessageBox::Critical);
	
	a.exec();
	ui.statusFrame->setStyleSheet(QLatin1String("background-color: rgb(112, 193, 50);"));
}

Mainwindow::~Mainwindow()
{
	delete loadcircle;
}

void Mainwindow::Draw_Point(uint, ldoub, ldoub, flag, Color)
{

}
void Mainwindow::Draw_Segment(uint, ldoub, ldoub, ldoub, ldoub, flag, Color)
{

}
void Mainwindow::Draw_Circle(uint, ldoub, ldoub, ldoub, flag, Color)
{

}
void Mainwindow::Draw_Line(uint, ldoub, ldoub, ldoub, flag, Color)
{

}

void Mainwindow::Write_Constraint(uint, V::TConstraint)
{

}