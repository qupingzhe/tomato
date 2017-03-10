#ifndef Q_TASK_H
#define Q_TASK_H
#include "tomato.h"
#include <QString>

class QTask
{
public:
	QTask( void );
	QTask( Task task );
	Task toTask( void );

	int id;
	QString classification;
	QString tag;
	QString name;
	int needingTime;
	bool choosed;
	bool finished;
};

#endif
