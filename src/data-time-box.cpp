#include "data-time-box.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>

#include "data-time-widget.h"

namespace tomato {

DataTimeCanvas::DataTimeCanvas(int start_minute, int end_minute, QWidget* parent)
  : QWidget(parent) {
	setMinimumWidth(900);
  start_minute_ = start_minute;
  end_minute_ = end_minute;
	//setMinimumWidth(90);
}

void DataTimeCanvas::paintEvent(QPaintEvent* event) {
  if (event->type() != QEvent::Paint) {
    return ;
  }
	int utilization_minutes = 0;
	QPainter painter(this);
	painter.setPen(Qt::NoPen);

	QString no_tag = QString::fromStdWString(L"空");

	int now_minute = start_minute_;
  int tmp;
	for (std::vector<QDataTime>::iterator i = data_times_.begin();
			i != data_times_.end(); ++i) {
		if (now_minute < (i->basic_data_time).start_minute) {
			painter.setBrush(QBrush(DataTimeWidget::GetColor(no_tag), Qt::SolidPattern));
      tmp = (i->basic_data_time).start_minute;
      if (tmp > end_minute_) {
        tmp = end_minute_;
      }
      painter.drawRect(now_minute - start_minute_, 0, tmp - now_minute, 20);
      now_minute = tmp;

      /*
			while (true) {
				if (now_minute >= (i->basic_data_time).start_minute) {
					break;
				}
				painter.drawRect(now_minute, 0, 1, 20);
				now_minute++;
				now_minute %= 900;
				if (now_minute == 0) {
					break;
				}
			}
      */
		}
    tmp = (i->basic_data_time).end_minute;
    if (tmp > end_minute_) {
      tmp = end_minute_;
    }
   	painter.setBrush(QBrush(DataTimeWidget::GetColor(i->tag), Qt::SolidPattern));
    painter.drawRect(now_minute - start_minute_, 0, tmp - now_minute, 20);
    utilization_minutes += tmp - now_minute;
    now_minute = tmp;

    /*
		for ( ; now_minute < (i->basic_data_time).end_minute; ++now_minute) {
			utilization_minutes++;
			painter.drawRect(now_minute, 0, 1, 20);
		}
    */

	}

	//int end_minute = 900;
  painter.setBrush(QBrush(DataTimeWidget::GetColor(no_tag), Qt::SolidPattern));
  painter.drawRect(now_minute - start_minute_, 0, end_minute_ - now_minute, 20);

  /*
	while (true) {
		if (now_minute >= end_minute) {
			break;
		}
		painter.drawRect(now_minute, 0, 1, 20);
		now_minute++;
		now_minute %= 900;
		if (now_minute == 0) {
			break;
		}
	}
  */
	emit ChangedUtilizationRate(utilization_minutes * 100
                               / (end_minute_ - start_minute_));
}

std::vector<QDataTime>& DataTimeCanvas::data_times() {
	return data_times_;
}


const QColor DataTimeBox::NO_USING_COLOR = QColor(Qt::black);

DataTimeBox::DataTimeBox(int day_offset, int start_minute, int end_minute,
                         QWidget* parent) : QWidget(parent) {
	day_offset_label_ = new QLabel(QString("%1").arg(day_offset));
	utilization_rate_label_ = new QLabel;
	layout_ = new QHBoxLayout;
	data_time_canvas_ = new DataTimeCanvas(start_minute, end_minute);

	utilization_time_ = 0;
	all_time_ = 0;

	connect(data_time_canvas_, SIGNAL(ChangedUtilizationRate(int)),
			this, SLOT(UtilizationRate(int)));

	layout_->addWidget(day_offset_label_);
	layout_->addWidget(data_time_canvas_);
	layout_->addWidget(utilization_rate_label_);
	setLayout(layout_);
}

DataTimeBox::~DataTimeBox() {
	delete layout_;
	delete data_time_canvas_;
	delete utilization_rate_label_;
  delete day_offset_label_;
}

std::vector<QDataTime>& DataTimeBox::data_times() {
	return data_time_canvas_->data_times();
}

void DataTimeBox::UtilizationRate(int rate) {
	utilization_rate_label_->setText(QString("%1%").arg(rate));
}

}

