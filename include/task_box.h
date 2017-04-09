#ifndef TASK_BOX_H
#define TASK_BOX_H

#include <QHBoxLayout>
#include "qtask.h"

class QCheckBox;
class QLabel;

class TaskWidget;

class TaskBox : public QHBoxLayout
{
	Q_OBJECT
public:
	TaskBox( QTask qtask, int hidingCheck, TaskWidget* parent);
	~TaskBox( void );
	void updateTask( QTask qtask );
	int getID( void );
	void show( void );
	void hide( void );
	void updateDisplay( void );
	void setHidingState( bool isHidingTask );
public slots:
	void chooseTask( int id );
	void finishTask( int id );
private:
	QTask qtask;
	bool isHidingTask;
	QCheckBox* finishTaskCheck;
	QCheckBox* chooseTaskCheck;
	TaskWidget* parent;
	QLabel* usingTime;
	QLabel* needingTime;
	QLabel* taskTag;
	QLabel* taskName;
	bool clearFlag;
};

#endif
