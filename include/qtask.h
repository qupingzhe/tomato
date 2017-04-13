#ifndef Q_TASK_H
#define Q_TASK_H
#include "task.h"
#include <QString>

class QTask : public BasicTask
{
public:
	QTask( void );
	QTask( Task task );
	Task toTask( void );

	QString tag;
	QString name;
};

#endif
