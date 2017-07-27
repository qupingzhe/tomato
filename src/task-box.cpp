#include "task-box.h"

#include <QLabel>
#include <QCheckBox>

#include "task-widget.h"

namespace tomato {

TaskBox::TaskBox(QTask qtask, int hiding_task, TaskWidget* parent) {
	qtask_ = qtask;
	parent_ = parent;
	hiding_task_ = (hiding_task == Qt::Checked)? false : true;
	clear_flag_ = false;

	finish_task_check_ = new QCheckBox;
	if (qtask.basic_task.finished) {
		finish_task_check_->setCheckState(Qt::Checked);
	}
	addWidget(finish_task_check_);

	using_time_ = new QLabel(QString::number(qtask.basic_task.using_time));
	addWidget(using_time_);
	
	needing_time_ = new QLabel(QString::number(qtask.basic_task.needing_time));
	addWidget(needing_time_);

	task_tag_ = new QLabel(qtask.tag);
	addWidget(task_tag_);

	task_name_ = new QLabel(qtask.name);
	addWidget(task_name_);

	choose_task_check_ = new QCheckBox;
	addWidget(choose_task_check_);

	connect(finish_task_check_, SIGNAL(stateChanged(int)),
			this, SLOT(FinishTask(int)));
	connect(choose_task_check_, SIGNAL(stateChanged(int)),
			this, SLOT(ChooseTask(int)));
	UpdateDisplay();
}

TaskBox::~TaskBox() {
	delete task_name_;
	delete finish_task_check_;
	delete choose_task_check_;
}

int TaskBox::GetID() {
	return qtask_.basic_task.id;
}

void TaskBox::UpdateTask(QTask qtask) {
	qtask_ = qtask;
	using_time_->setText(QString::number(qtask.basic_task.using_time));
	if (qtask.basic_task.finished) {
		finish_task_check_->setCheckState(Qt::Checked);
	} else {
		finish_task_check_->setCheckState(Qt::Unchecked);
	}

	clear_flag_ = true;
	if (qtask.basic_task.choosed) {
		choose_task_check_->setCheckState(Qt::Checked);
	} else {
		choose_task_check_->setCheckState(Qt::Unchecked);
	}
	clear_flag_ = false;
}

void TaskBox::FinishTask(int state) {
	parent_->FinishChildTask(qtask_.basic_task.id, state == Qt::Checked);
}

void TaskBox::ChooseTask(int state) {
	if (!clear_flag_) {
		parent_->ChooseChildTask(qtask_.basic_task.id, state == Qt::Checked);
	}
}

void TaskBox::set_hiding_task(bool hiding_task) {
  hiding_task_ = hiding_task;
	UpdateDisplay();
}

void TaskBox::UpdateDisplay() {
	if (qtask_.basic_task.finished && hiding_task_) {
		Hide();
	} else {
		Show();
	}
}

void TaskBox::Hide() {
	finish_task_check_->hide();
	choose_task_check_->hide();
	using_time_->hide();
	needing_time_->hide();
	task_tag_->hide();
	task_name_->hide();
}

void TaskBox::Show() {
	finish_task_check_->show();
	choose_task_check_->show();
	using_time_->show();
	needing_time_->show();
	task_tag_->show();
	task_name_->show();
}

}

