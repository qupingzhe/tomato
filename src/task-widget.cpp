#include "task-widget.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>

#include "task-box.h"
#include "time-dialog.h"

namespace tomato {

TaskWidget::TaskWidget() {
	work_time_box_ = new QSpinBox;
	rest_time_box_ = new QSpinBox;
	
	start_button_ = new QPushButton(tr("start"));
	connect(start_button_, SIGNAL(clicked()),
			this, SLOT(DoStart()) );
	connect(work_time_box_, SIGNAL(valueChanged(int)),
			this, SLOT(WorkTime(int)));
	connect(rest_time_box_, SIGNAL(valueChanged(int)),
			this, SLOT(RestTime(int)));

	show_finish_ = new QCheckBox(tr("finish?"));

	mid_layout_ = new QVBoxLayout;
	mid_layout_->addStretch(0);
	mid_layout_->addWidget(work_time_box_);
	mid_layout_->addWidget(rest_time_box_);
	mid_layout_->addWidget(start_button_);
	mid_layout_->addStretch(0);

	left_layout_ = new QVBoxLayout;

	QHBoxLayout* task_title;
	task_title = new QHBoxLayout;
	task_title->addWidget(show_finish_);
	task_title->addWidget(new QLabel(tr("using")));
	task_title->addWidget(new QLabel(tr("needing")));
	task_title->addWidget(new QLabel(tr("tag")));
	task_title->addWidget(new QLabel(tr("name")));
	task_title->addWidget(new QLabel(tr("choose?")));

	connect(show_finish_, SIGNAL(stateChanged(int)),
			this, SLOT(HideTask(int)));
	show_finish_->setCheckState(Qt::Unchecked);

	left_layout_->addStretch(1);
	left_layout_->addLayout(task_title);

	main_layout_ = new QHBoxLayout;
	main_layout_->addLayout(left_layout_);
	main_layout_->addLayout(mid_layout_);
	setLayout(main_layout_);
}

TaskWidget::~TaskWidget() {
	delete mid_layout_;
	delete left_layout_;
	delete main_layout_;

	delete start_button_;
	delete rest_time_box_;
	delete work_time_box_;
	for (std::vector<TaskBox*>::iterator i = task_group_.begin();
      i != task_group_.end(); ++i) {
		//delete *i;
	}
	task_group_.clear();
}

void TaskWidget::Load() {
	work_time_box_->setValue(25);
	rest_time_box_->setValue(5);
}

void TaskWidget::FinishChildTask(int id, bool status) {
	emit FinishTask(id, status);
}

void TaskWidget::ChooseChildTask(int id, bool status) {
	emit ChooseTask(id, status);
}

void TaskWidget::UpdateTask(QTask qtask) {
	size_t ptr = 0;
	size_t task_number = task_group_.size();
	for ( ; ptr < task_number; ++ptr) {
		if (task_group_[ptr]->GetID() == qtask.basic_task.id) {
			break;
		}
	}
	if (ptr == task_number) {
		TaskBox* tmp = new TaskBox(qtask, show_finish_->checkState(), this);
		task_group_.push_back(tmp);
		left_layout_->addLayout(tmp);
	} else {
		task_group_[ptr]->UpdateTask(qtask);
		task_group_[ptr]->UpdateDisplay();
	}
}

void TaskWidget::UpdateTask(const std::vector<QTask>& qtasks) {
	for (std::vector<QTask>::const_iterator i = qtasks.begin();
      i != qtasks.end(); ++i ) {
		UpdateTask(*i);
	}
}

void TaskWidget::DoStart() {
	emit Start();
}

void TaskWidget::HideTask(int state) {
	bool hiding_task = state==Qt::Checked?false:true;
	for (std::vector<TaskBox*>::iterator i = task_group_.begin();
      i != task_group_.end(); ++i ) {
		(*i)->set_hiding_task(hiding_task);
	}
}

void TaskWidget::WorkTime(int minutes) {
	emit WorkTimeChanged(minutes);
}

void TaskWidget::RestTime(int minutes) {
	emit RestTimeChanged(minutes);
}

}

