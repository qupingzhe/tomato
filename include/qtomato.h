#ifndef Q_TOMATO_H
#define Q_TOMATO_H

#include <QObject>
#include <QString>
#include "tomato.h"
#include "qtask.h"

class QTimer;

class QTomato : public QObject
{
	Q_OBJECT
public:
	QTomato( void );
	void setTime( int workTime, int restTime );
	void load( void );
	void doFinishWork( void );
	~QTomato( void );
signals:
	void finishWork( void );
	void finishRest( void );
	void updateTask( QTask qtask );
	void changeTime( int remainingTime );
public slots:
	void addTask( QTask qtask );
	void chooseTask( int id );
	void finishTask( int id );
	void start( void );
private slots:
	void timeout( void );
private:
	int workTime;
	int restTime;
	int totalTime;
	int remainingTime;
	Tomato* tomato;
	QTimer* timer;
};

#endif
