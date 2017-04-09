#include "timer.h"
#include <QTimer>

TomatoTimer::TomatoTimer( void )
{
	this->timer = new QTimer;
	connect( timer, SIGNAL(timeout()),
			this, SLOT(timeout()) );
}

TomatoTimer::~TomatoTimer( void )
{
	timer->stop();
	delete timer;
}

void TomatoTimer::start( void )
{
	remainingTime = workTime + restTime;
	if( remainingTime > 0 ) {
		emit displayTime( remainingTime-restTime );
		timer->start( 1000 );
	}
}

void TomatoTimer::setTime( int workTime, int restTime )
{
	//this->workTime = workTime*60;
	//this->restTime = restTime*60;
	this->workTime = workTime;
	this->restTime = restTime;
	this->remainingTime = this->workTime + this->restTime;
	emit displayTime( this->workTime );
}

void TomatoTimer::timeout( void )
{
	--remainingTime;
	if( remainingTime == restTime ) {
		emit finishWork();
	}
	if( remainingTime == 0 ) {
		emit finishRest();
		timer->stop();
		return ;
	}
	int tmp = remainingTime > restTime ? remainingTime-restTime : remainingTime;
	emit displayTime( tmp );
	timer->start( 1000 );
}

