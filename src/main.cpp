#include <QApplication>
#include "main_window.h"
#include <iostream>

int main( int argc, char** argv )
{
	QApplication app( argc, argv );
	std::wcout.imbue( std::locale( "zh_CN.UTF-8" ) );
	const wchar_t* s= L"记得置顶！！！！！！！！！！！！！！";
	std::wcout << s << std::endl;
	TomatoMainWindow* mainWindow = new TomatoMainWindow;
	//TomatoMainWindow mainWindow;
	mainWindow->show();
	int rs = app.exec();
	delete mainWindow;
	return rs;
}
