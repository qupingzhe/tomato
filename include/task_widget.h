#ifndef TASK_WIDGET_H
#define TASK_WIDGET_H

#include "qtask.h"

#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include <map>

class QPushButton;
class QVBoxLayout;
class QSpinBox;
class QCheckBox;
class QLabel;

class TimeDialog;

class TaskWidget;
class GroupTask : public QHBoxLayout
{
	Q_OBJECT
public:
	GroupTask( QTask qtask, TaskWidget* parent);
	~GroupTask( void );
public slots:
	void chooseTask( int id );
	void finishTask( int id );
private:
	QCheckBox* finishTaskCheck;
	QCheckBox* chooseTaskCheck;
	TaskWidget* parent;
	int id;
	QLabel* taskName;
};


class TaskWidget : public QWidget
{
	Q_OBJECT
public:
	TaskWidget( void );
	~TaskWidget( void );
	void finishChildTask( int id );
	void chooseChildTask( int id );
signals:
	void start( void );
	void chooseTask( int id );
	void finishTask( int id );
public slots:
	void getTask( QTask qtask );
private slots:
	void doStart( void );
private:
	std::map<int, QTask> taskList;
	std::vector<GroupTask*> taskGroup;
	QSpinBox* workingTime;
	QSpinBox* restingTime;
	QPushButton* startButton;
	QVBoxLayout* leftLayout;
	QVBoxLayout* midLayout;
	QHBoxLayout* mainLayout;
};

#endif
