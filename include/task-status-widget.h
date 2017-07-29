#ifndef TOMATO_TASK_STATUS_WIDGET_H
#define TOMATO_TASK_STATUS_WIDGET_H

#include <QHBoxLayout>
#include <QWidget>

#include <vector>

#include "qtask.h"

class QLabel;
class QVBoxLayout;
class QPushButton;
class QDateTimeEdit;

namespace tomato {

class TaskStatusBox : public QHBoxLayout {
public:
  TaskStatusBox(QString title);
  ~TaskStatusBox();
  void Update(const QString& number, const QString& average_time,
              const QString& average_needing_time,
              const QString& average_using_time,
              const QString& opition);
private:
  QLabel* title_;
  QLabel* number_;
  QLabel* average_using_time_;
  QLabel* average_needing_time_;
  QLabel* average_time_;
  QLabel* opition_;

  QVBoxLayout* right_layout_;
  QHBoxLayout* mid_layout_;
};

class TaskStatusWidget : public QWidget {
  Q_OBJECT
public:
  TaskStatusWidget(QWidget* parent = NULL);
public slots:
  void UpdateTask(const std::vector<QTask>& data_times);
private slots:
  void FlushTask();
private:
  QDateTimeEdit* start_time_;
  QDateTimeEdit* end_time_;
  QPushButton* flush_button_;
  TaskStatusBox* task_finished_box_;
  TaskStatusBox* task_doing_box_;

  QVBoxLayout* main_layout_;
  QHBoxLayout* top_layout_;
  std::vector<BasicTask> task_;
};

}

#endif
