#include "data-time-widget.h"

#include <QPainter>
#include <QVBoxLayout>
//#include <iostream>

#include "data-time-box.cpp"

namespace tomato {

const int MAX_DAY_OFFSET = 7;

DataTimeWidget::DataTimeWidget(QWidget* parent) : QWidget(parent) {
	layout_ = new QVBoxLayout;
	data_time_box_ = new DataTimeBox*[MAX_DAY_OFFSET];
	for (int i = 0; i <= MAX_DAY_OFFSET; ++i) {
		data_time_box_[i] = new DataTimeBox(i);
		layout_->addWidget(data_time_box_[i]);
	}
	setLayout(layout_);
}

DataTimeWidget::~DataTimeWidget() {
	for (int i = 0; i <= MAX_DAY_OFFSET; ++i) {
		delete data_time_box_[i];
	}
	delete[] data_time_box_;
	delete layout_;
}

void DataTimeWidget::UpdateDataTime(const std::vector<QDataTime>& data_times) {
	for (int i = 0; i <= MAX_DAY_OFFSET; ++i) {
		data_time_box_[i]->data_times().clear();
	}
	for (std::vector<QDataTime>::const_iterator i = data_times.begin();
			i != data_times.end(); ++i ) {
		data_time_box_[(i->basic_data_time).day_offset]->data_times().push_back(*i);
	}
}

}

