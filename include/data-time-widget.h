#ifndef TOMATO_DATA_TIME_WIDGET_H
#define TOMATO_DATA_TIME_WIDGET_H

#include <QWidget>
#include <vector>

#include "qtask.h"

class QVBoxLayout;

namespace tomato {

class DataTimeBox;

class DataTimeWidget : public QWidget {
	Q_OBJECT
public:
	DataTimeWidget(QWidget* parent = NULL);
	~DataTimeWidget();

  /*
	static QColor GetColor(QString tag) {
		static const QString book = QString::fromStdWString(L"看书");
		static const QString blog = QString::fromStdWString(L"博客");
		static const QString project = QString::fromStdWString(L"项目");
		static const QString algorithm = QString::fromStdWString(L"算法");
		static const QString homework = QString::fromStdWString(L"作业");
		static const QString school = QString::fromStdWString(L"课堂");
		Qt::GlobalColor value;
		if (tag ==  book) {
			value = Qt::blue;
		} else if (tag == blog) {
			value = Qt::green;
		} else if (tag == project) {
			value = Qt::red;
		} else if (tag == algorithm) {
			value = Qt::yellow;
		} else if (tag == homework) {
			value = Qt::white;
		} else if (tag == school) {
			value = Qt::cyan;
		} else {
			value = Qt::black;
		}
		return QColor(value);
	}
  */

public slots:
	void UpdateDataTime(const std::vector<QDataTime>& data_times);
private:
	std::vector<QDataTime> data_times_;

	QVBoxLayout* layout_;
	DataTimeBox** data_time_box_;
};

}

#endif
