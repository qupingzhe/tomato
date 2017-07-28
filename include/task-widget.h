#ifndef TOMATO_TASK_WIDGET_H
#define TOMATO_TASK_WIDGET_H

#include <QWidget>

#include <vector>
#include <map>

#include "qtask.h"
#include "task-box.h"

class QSpinBox;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;


namespace tomato {

class TimeDialog;

class TaskWidget : public QWidget {
	Q_OBJECT
public:
	TaskWidget();
	~TaskWidget();
	void Load();
	void FinishChildTask(int id, bool status);
	void ChooseChildTask(int id, bool status);
signals:
	void Start(void);
	void ChooseTask(int id, bool status);
	void FinishTask(int id, bool status);
	void WorkTimeChanged(int minutes);
	void RestTimeChanged(int minutes);
public slots:
	void UpdateTask(const std::vector<QTask>& qtasks);
	void UpdateTask(QTask qtask);
private slots:
	void DoStart();
	void HideTask(int state);
	void WorkTime(int minutes);
	void RestTime(int minutes);
private:
	std::vector<TaskBox*> task_group_;
	QSpinBox* work_time_box_;
	QSpinBox* rest_time_box_;
	QPushButton* start_button_;
	QVBoxLayout* left_layout_;
	QVBoxLayout* mid_layout_;
	QHBoxLayout* main_layout_;
	QCheckBox* show_finish_;
};

}

#endif
