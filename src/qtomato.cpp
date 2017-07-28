#include "qtomato.h"

#include <iostream>

namespace tomato {
QTomato::QTomato() {
	tomato_ = new Tomato();
}

QTomato::~QTomato() {
	delete tomato_;
  tasks_.clear();
  data_times_.clear();
}

void QTomato::Load() {
	tomato_->Load();
	Flush();
}

void QTomato::Flush() {
	FlushTask();
	FlushDataTime();
}

void QTomato::FlushTask() {
	tasks_.clear();
	for (std::map<int,Task>::const_iterator i = tomato_->BeginForTask();
			i != tomato_->EndForTask(); ++i) {
		tasks_.push_back(QTask(i->second));
	}
	emit UpdateTask(tasks_);
}

void QTomato::FlushDataTime() {
	tomato_->FlushDataTime();
	data_times_.clear();
	for (std::vector<DataTime>::const_iterator i = tomato_->BeginForDataTime();
			i != tomato_->EndForDataTime(); ++i ) {
		data_times_.push_back(QDataTime(*i));
	}
	emit UpdateDataTime(data_times_);
}

void QTomato::Start(int work_time, int rest_time) {
	tomato_->Start(work_time, rest_time);
}

void QTomato::End() {
	tomato_->End();
	Flush();
}

void QTomato::AddTask(QTask qtask) {
	int id = tomato_->AddTask(qtask.ToTask());
	emit UpdateTask(QTask(tomato_->GetTask(id)));
}

void QTomato::ChooseTask(int id, bool status) {
	tomato_->ChooseTask(id, status);
	emit UpdateTask(QTask(tomato_->GetTask(id)));
}

void QTomato::FinishTask(int id, bool status) {
	tomato_->FinishTask(id, status);
	emit UpdateTask(QTask(tomato_->GetTask(id)));
}

}
