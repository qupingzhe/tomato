#include "qtask.h"

QTask::QTask( void )
{
}

QTask::QTask( Task task )
{
	id = task.id;

	classification = QString::fromStdWString(task.classification);
	tag = QString::fromStdWString(task.tag);
	name = QString::fromStdWString(task.name);

	needingTime = task.needingTime;
	choosed = task.choosed;
	finished = task.finished;
}

Task QTask::toTask( void )
{
	Task task;
	task.id = id;
	
	task.classification = classification.toStdWString();
	task.tag = tag.toStdWString();
	task.name = name.toStdWString();

	task.needingTime = needingTime;
	task.choosed = choosed;
	task.finished = finished;
	return task;
}
