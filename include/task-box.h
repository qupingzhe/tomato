#ifndef TOMATO_TASK_BOX_H
#define TOMATO_TASK_BOX_H

#include <QHBoxLayout>
#include "qtask.h"

class QCheckBox;
class QLabel;

namespace tomato {

class TaskWidget;

class TaskBox : public QHBoxLayout {
	Q_OBJECT
public:
	TaskBox(QTask qtask, int hidingCheck, TaskWidget* parent);
	~TaskBox();
	void UpdateTask(QTask qtask);
	int GetID();
	void Show();
	void Hide();
	void UpdateDisplay();
	void set_hiding_task(bool hiding_task);
public slots:
	void ChooseTask(int id);
	void FinishTask(int id);
private:
	QTask qtask_;
	bool hiding_task_;
	QCheckBox* finish_task_check_;
	QCheckBox* choose_task_check_;
	TaskWidget* parent_;
	QLabel* using_time_;
	QLabel* needing_time_;
	QLabel* task_tag_;
	QLabel* task_name_;
	bool clear_flag_;
};

}

#endif
