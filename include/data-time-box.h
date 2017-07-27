#ifndef Task_DATA_BOX_H
#define TASK_DATA_BOX_H

#include <QWidget>

#include "qtask.h"

class QLabel;
class QHBoxLayout;

namespace tomato {

class DataTimeCanvas : public QWidget {
	Q_OBJECT
public:
	DataTimeCanvas(QWidget* parent = NULL);
	void paintEvent(QPaintEvent* event);
	std::vector<QDataTime>& data_times();
signals:
	void ChangedUtilizationRate(int rate);
private:
	std::vector<QDataTime> data_times_;
};


class DataTimeBox : public QWidget {
	Q_OBJECT
public:
	static const QColor NO_USING_COLOR;

	DataTimeBox(int day_offset, QWidget* parent = NULL);
	~DataTimeBox();
	std::vector<QDataTime>& data_times();
private slots:
	void UtilizationRate(int rate);

private:
	QLabel* day_offset_label_;
	QLabel* utilization_rate_label_;
	DataTimeCanvas* data_time_canvas_;

	int utilization_time_;
	int all_time_;

	QHBoxLayout* layout_;
};

}

#endif
