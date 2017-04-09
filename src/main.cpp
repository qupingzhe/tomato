#include <QApplication>
#include "main_window.h"
#include <iostream>

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	std::wcout.imbue( std::locale( "zh_CN.UTF-8" ) );
	std::wcout << L"记得置顶！！！！！！！！！！！！！！" << std::endl;
	TomatoMainWindow* mainWindow = new TomatoMainWindow;
	mainWindow->show();
	int rs = app.exec();
	delete mainWindow;
	return rs;
}
