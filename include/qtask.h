#ifndef Q_TASK_H
#define Q_TASK_H

#include <QString>
#include "task.h"

namespace tomato {

struct QTask {
	QTask();
	QTask(const Task& task);
	Task ToTask();

  BasicTask basic_task;
	QString tag;
	QString name;
};

struct QDataTime {
	QDataTime(const DataTime& data_time);
	DataTime ToDataTime();

  BasicDataTime basic_data_time;
	QString tag;
  QString name;
};

}

#endif
