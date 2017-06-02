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
	void flushTask( void );
	void flushTaskData( void );
signals:
	void updateTask( QTask qtask );
	void updateTask( const std::vector<QTask> &qtasks );
	void updateTaskData( const std::vector<QTaskData>& qtaskDatas );
public slots:
	void addTask( QTask qtask );
	void chooseTask( int id, bool status );
	void finishTask( int id, bool status );

	void start( int workingTime, int restingTime );
	void end( void );
private:
	Tomato* tomato;
	std::vector<QTask> tasks;
	std::vector<QTaskData> taskDatas;
};

#endif
