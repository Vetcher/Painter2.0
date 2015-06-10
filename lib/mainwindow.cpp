#include "mainwindow.h"
#include "qmessagebox.h"
#include "qstring.h"
#include "qstringlist.h"
#include "qheaderview.h"

Mainwindow::Mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	// load user graphics interface
	ui.setupUi(this);
	loadcircle = new QMovie(":/icons/loader.gif");
	loadcircle->setSpeed(200);
	ui.loadBar->setMovie(loadcircle);

	// manual setup ui
	LoadCircleStart();

	showMaximized();
	ui.graphicsSpace->Connect(&_storage);
	_toolsbuttons = new QButtonGroup;
	_toolsbuttons->addButton(ui.toolSelectBTN);
	_toolsbuttons->addButton(ui.toolPointBTN);
	//ui.tableWidgetObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Fixed);
	ui.tableWidgetObjects->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui.tableWidgetObjects->horizontalHeader()->resizeSection(0, 40);
	ui.tableWidgetConstraints->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui.tableWidgetProperties->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
	ui.tableWidgetObjects->setHorizontalHeaderLabels(QStringList() << "ID" << "Type" << "x1" << "y1" << "x2" << "y2");
	ui.tableWidgetProperties->setHorizontalHeaderLabels(QStringList() << "Property" << "Value");
	ui.tableWidgetConstraints->setHorizontalHeaderLabels(QStringList() << "ID" << "Type");

	// ---------------
	LoadCircleStop();

	// other functions
	//WriteError("Error", "Tests on start");
}

void Mainwindow::ClearScene()
{
	ui.graphicsSpace->ClearScene();
	ui.tableWidgetObjects->clearContents();
	ui.tableWidgetObjects->setRowCount(0);
}

void Mainwindow::updateSpace()
{
	ClearScene();
	_storage.Upload_All_To(*this);
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
	delete _toolsbuttons;
}

void Mainwindow::Draw_Point(uint id, double x, double y, flag f, Color c)
{
	while (true)
	{
		ui.graphicsSpace->Draw_Point(id, x, y, f, c);
		ui.tableWidgetObjects->insertRow(ui.tableWidgetObjects->rowCount());
		QTableWidgetItem* item = new QTableWidgetItem;
		item->setText(QString().setNum(id));
		ui.tableWidgetObjects->setItem(ui.tableWidgetObjects->rowCount() - 1, 0, item);
		item = new QTableWidgetItem;
		item->setText("Point");
		ui.tableWidgetObjects->setItem(ui.tableWidgetObjects->rowCount() - 1, 1, item);
		item = new QTableWidgetItem;
		item->setText(QString().setNum(x));
		ui.tableWidgetObjects->setItem(ui.tableWidgetObjects->rowCount() - 1, 2, item);
		item = new QTableWidgetItem;
		item->setText(QString().setNum(y));
		ui.tableWidgetObjects->setItem(ui.tableWidgetObjects->rowCount() - 1, 3, item);
		ui.tableWidgetObjects->clearContents();
	}
}
void Mainwindow::Draw_Segment(uint id, double x1, double y1, double x2, double y2, flag f, Color c)
{
	ui.graphicsSpace->Draw_Segment(id, x1, y1, x2, y2, f, c);
}
void Mainwindow::Draw_Circle(uint id, double x, double y, double r, flag f, Color c)
{
	ui.graphicsSpace->Draw_Circle(id, x, y, r, f, c);
}
void Mainwindow::Draw_Line(uint id, double A, double B, double C, flag f, Color c)
{
	ui.graphicsSpace->Draw_Line(id, A, B, C, f, c);
}

void Mainwindow::Write_Constraint(uint id, V::TConstraint type)
{

}