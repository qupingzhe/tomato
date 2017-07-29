#include "task-status-widget.h"

#include <ctime>
//#include <iostream>
#include <cmath>

#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDateTimeEdit>
#include <QDate>
#include <QTime>

namespace tomato {

TaskStatusBox::TaskStatusBox(QString title) {
  title_ = new QLabel(title);
  number_ = new QLabel(tr("Number:"));
  average_time_ = new QLabel(tr("Average Time"));
  average_using_time_ = new QLabel(tr("Average Using time"));
  average_needing_time_ = new QLabel(tr("Average Needing Time"));
  opition_ = new QLabel(tr("Opition"));

  mid_layout_ = new QHBoxLayout;
  mid_layout_->addWidget(average_using_time_);
  mid_layout_->addWidget(average_needing_time_);
  mid_layout_->addWidget(opition_);

  right_layout_ = new QVBoxLayout;
  right_layout_->addWidget(number_);
  right_layout_->addLayout(mid_layout_);
  right_layout_->addWidget(average_time_);

  addWidget(title_);
  addLayout(right_layout_);
}

TaskStatusBox::~TaskStatusBox() {

}

void TaskStatusBox::Update(const QString& number, const QString& average_time,
                           const QString& average_needing_time,
                           const QString& average_using_time,
                           const QString& opition) {
  number_->setText(number);
  number_->show();

  average_using_time_->setText(average_using_time);
  average_using_time_->show();

  average_needing_time_->setText(average_needing_time);
  average_needing_time_->show();

  average_time_->setText(average_time);
  average_time_->show();

  opition_->setText(opition);
  opition_->show();
}


TaskStatusWidget::TaskStatusWidget(QWidget* parent) : QWidget(parent) {
  start_time_ = new QDateTimeEdit(QDateTime(QDate(2017, 5, 20), QTime(0,0)));
  end_time_ = new QDateTimeEdit(QDateTime(QDate(2017, 7, 29), QTime(11,0)));
  flush_button_ = new QPushButton(tr("Flush"));
  top_layout_ = new QHBoxLayout;
  top_layout_->addWidget(start_time_);
  top_layout_->addWidget(end_time_);
  top_layout_->addWidget(flush_button_);

  task_finished_box_ = new TaskStatusBox(QString(tr("finished")));
  task_doing_box_ = new TaskStatusBox(QString(tr("doing")));

  main_layout_ = new QVBoxLayout;
  main_layout_->addLayout(top_layout_);
  main_layout_->addLayout(task_finished_box_);
  main_layout_->addLayout(task_doing_box_);

  setLayout(main_layout_);

  connect(flush_button_, SIGNAL(clicked()),
      this, SLOT(FlushTask()));
}

void TaskStatusWidget::UpdateTask(const std::vector<QTask>& data_times) {
  task_.clear();
  for (std::vector<QTask>::const_iterator i = data_times.begin();
      i != data_times.end(); ++i) {
    task_.push_back(i->basic_task);
  }
  FlushTask();
}

void TaskStatusWidget::FlushTask() {
  time_t start_seconds = start_time_->dateTime().toUTC().toTime_t();
  time_t end_seconds = end_time_->dateTime().toUTC().toTime_t();

  struct {
    int number;
    int using_time;
    int needing_time;
    time_t d_minute_time;
    void add(int using_time, int needing_time, time_t d_minute_time) {
      this->number++;
      this->using_time += using_time;
      this->needing_time += needing_time;
      this->d_minute_time += d_minute_time;
    }
  } finished_data, doing_data;

  memset(&finished_data, 0, sizeof(finished_data));
  memset(&doing_data, 0, sizeof(doing_data));

  double estimated_accuracy = 0.0;
  for (std::vector<BasicTask>::iterator i = task_.begin(); i != task_.end(); ++i) {
    if (i->creating_time < start_seconds || i->creating_time > end_seconds) {
      continue;
    }

    if (!i->finished) {
      doing_data.add(i->using_time, i->needing_time,
          (end_seconds - i->creating_time)/60);
    } else if (i->finishing_time < start_seconds ||
               i->finishing_time > end_seconds) {
      doing_data.add(i->using_time, i->needing_time,
          (end_seconds - i->creating_time)/60);
    } else {
      finished_data.add(i->using_time, i->needing_time,
          (i->finishing_time - i->creating_time)/60);
      double d_time = fabs(i->using_time - i->needing_time) * 1.0;
      estimated_accuracy += d_time * 100.0 / i->needing_time;
    }
  }

  if (doing_data.number == 0) {
    task_doing_box_->Update(
        QString(tr("Number: 0")),
        QString(tr("Average Time: N/A")),
        QString(tr("Average Needing Time: N/A")),
        QString(tr("Average Using Time: N/A")),
        QString(tr("Opition: N/A")));
  } else {
    task_doing_box_->Update(
        QString(tr("Number: %1")).arg(doing_data.number),
        QString(tr("Average Time: %1"))
            .arg(doing_data.d_minute_time * 1.0 / doing_data.number),
        QString(tr("Average Needing Time: %1"))
            .arg(doing_data.needing_time * 1.0 / doing_data.number),
        QString(tr("Average Using Time: %1"))
            .arg(doing_data.using_time * 1.0 / doing_data.number),
        QString(tr("Opition: N/A")));
  }
  if (finished_data.number == 0) {
    task_finished_box_->Update(
        QString(tr("Number: 0")),
        QString(tr("Average Time: N/A")),
        QString(tr("Average Needing Time: N/A")),
        QString(tr("Average Using Time: N/A")),
        QString(tr("Averate Estimated Accuracy: N/A")));
    return ;
  }
  task_finished_box_->Update(
      QString(tr("Number: %1")).arg(finished_data.number),
      QString(tr("Average Time: %1"))
          .arg(finished_data.d_minute_time * 1.0 / finished_data.number),
      QString(tr("Average Needing Time: %1"))
          .arg(finished_data.needing_time * 1.0 / finished_data.number),
      QString(tr("Average Using Time: %1"))
          .arg(finished_data.using_time * 1.0 / finished_data.number),
      QString(tr("Average Estimated Accuracy: %1%"))
          .arg(estimated_accuracy / finished_data.number, 0, 'g', 4));
}

}

