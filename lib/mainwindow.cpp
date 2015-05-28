#include "mainwindow.h"
#include "qdialog.h"
#include "qstring.h"

Mainwindow::Mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	/*QDialog a;
	a.setWindowTitle(QString().setNum(sizeof(long unsigned)));
	a.exec();*/
	ui.setupUi(this);
}

Mainwindow::~Mainwindow()
{

}
