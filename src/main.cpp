#include <QApplication>
#include <iostream>

#include "main-window.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
	std::wcout.imbue(std::locale("zh_CN.UTF-8"));
	std::wcout << L"记得置顶！！！！！！！！！！！！！！" << std::endl;
  tomato::MainWindow* mainWindow = new tomato::MainWindow;
	mainWindow->show();
	int rs = app.exec();
	delete mainWindow;
	return rs;
}
