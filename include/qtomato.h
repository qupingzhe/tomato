#ifndef Q_TOMATO_H
#define Q_TOMATO_H

#include <QObject>
#include <QString>
#include "qtask.h"

#include "tomato.h"

class QTimer;

class QTomato : public QObject
{
	Q_OBJECT
public:
	QTomato( void );
	~QTomato( void );
	void load( void );
	void flush( void );
signals:
	void updateTask( std::vector<QTask> &qtasks );
	void updateTask( QTask qtask );
public slots:
	void addTask( QTask qtask );
	void chooseTask( int id );
	void finishTask( int id );
	void start( int workingTime, int restingTime );
	void end( void );
	void getTaskData( std::vector<QTaskData>& qtaskDatas );
private:
	Tomato* tomato;
	std::vector<int> tasksID;
	std::vector<QTask> tasks;
	std::vector<TaskData> taskDatas;
};

#endif
