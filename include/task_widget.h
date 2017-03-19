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
	GroupTask( QTask qtask, int hidingCheck, TaskWidget* parent);
	~GroupTask( void );
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
	void updateTask( QTask qtask );
private slots:
	void doStart( void );
	void hideTask( int state );
private:
	std::vector<GroupTask*> taskGroup;
	QSpinBox* workingTime;
	QSpinBox* restingTime;
	QPushButton* startButton;
	QVBoxLayout* leftLayout;
	QVBoxLayout* midLayout;
	QHBoxLayout* mainLayout;
	QCheckBox* showFinish;
};

#endif
