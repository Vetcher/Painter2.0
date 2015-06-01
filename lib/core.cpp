#include "core.h"

Core::Core(int argc, char** argv)
{
	a = new QApplication(argc, argv);
	mainw = new Mainwindow();
}

int Core::work()
{
	mainw->show();
	return a->exec();
}

Core::~Core()
{
	delete mainw;
	delete a;
}