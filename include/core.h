#pragma once
#include "mainwindow.h"
#include "QtWidgets/qapplication.h"
#include "GlobalStorage.h"

class Core
{
private:
	QApplication* a;
	Mainwindow* mainw;
	GlobalStorage storage;
public:
	Core(int, char**);
	int work();
	~Core();
};