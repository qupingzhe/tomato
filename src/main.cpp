#include <QApplication>
#include <iostream>

#include <QDataStream>
#include <QFile>
#include <QString>
#include "main-window.h"

int main(int argc, char** argv) {
	QApplication app(argc, argv);
  QFile file("./out");
  file.open(QIODevice::WriteOnly);
  QColor color(Qt::red);
  QDataStream out(&file);
  //out << color.red() << " " << color.green() << " " << color.yellow();
  out << QString("呵呵");

	std::wcout.imbue(std::locale("zh_CN.UTF-8"));
	std::wcout << L"记得置顶！！！！！！！！！！！！！！" << std::endl;
  tomato::MainWindow* mainWindow = new tomato::MainWindow;
	mainWindow->show();
	int rs = app.exec();
	delete mainWindow;
	return rs;
}
