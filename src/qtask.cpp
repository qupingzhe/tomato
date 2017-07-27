#include "qtask.h"

namespace tomato {

QTask::QTask() {
	;
}

QTask::QTask(const  Task& task ) {
  basic_task = task.basic_task;
	tag = QString::fromStdWString(task.tag);
	name = QString::fromStdWString(task.name);
}

Task QTask::ToTask() {
	Task task;
  task.basic_task = basic_task;
	task.tag = tag.toStdWString();
	task.name = name.toStdWString();
	return task;
}


QDataTime::QDataTime(const DataTime& data_time) {
  basic_data_time = data_time.basic_data_time;
	tag = QString::fromStdWString(data_time.tag);
	name = QString::fromStdWString(data_time.name);
}

DataTime QDataTime::ToDataTime() {
  DataTime data_time;
  data_time.basic_data_time = basic_data_time;
	data_time.tag = tag.toStdWString();
  data_time.name = name.toStdWString();
	return data_time;
}

}
