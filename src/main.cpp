#include <QApplication>
#include "main_window.h"
#include <iostream>

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	std::cout << "记得置顶！！！！！！！！！！！！！！" << std::endl;
	TomatoMainWindow* mainWindow = new TomatoMainWindow;
	mainWindow->show();
	return app.exec();
}
