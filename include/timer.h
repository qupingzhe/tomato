#ifndef TOMATO_TIME_H
#define TOMATO_TIME_H

#include <QObject>

class QTimer;

class TomatoTimer : public QObject
{
	Q_OBJECT
public:
	TomatoTimer( void );
	~TomatoTimer( void );
	void setTime( int workTime, int restTime );
signals:
	void finishWork();
	void finishRest();
	void displayTime( int time );
public slots:
	void start();
private slots:
	void timeout();
private:
	QTimer* timer;
	int remainingTime;
	int restTime;
	int workTime;
};

#endif
