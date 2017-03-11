#include "qtomato.h"

#include <QTimer>

#include <iostream>

QTomato::QTomato( void )
{
	tomato = new Tomato();
	timer = new QTimer;

	connect( timer, SIGNAL(timeout()),
			this, SLOT(timeout()) );
}

QTomato::~QTomato( void )
{
	std::wcout << L"~QTomato" << std::endl;
	delete tomato;
	delete timer;
}

void QTomato::load( void )
{
	for( int i=1; i<= Task::ID; ++i ) {
		emit getTask( QTask(tomato->getTask(i)) );
	}
}

void QTomato::setTime( int workTime, int restTime )
{
	//this->workTime = workTime*60;
	//this->restTime = restTime*60;
	this->workTime = workTime;
	this->restTime = restTime;
	this->totalTime = this->workTime + this->restTime;
}

void QTomato::addTask( QTask qtask )
{
	int id = tomato->addTask( qtask.toTask() );
	emit getTask( QTask(tomato->getTask(id)) );
}

void QTomato::chooseTask( int id )
{
	tomato->chooseTask( id );
}

void QTomato::finishTask( int id )
{
	tomato->finishTask( id );
}

/*
void QTomato::getAllTask( void )
{

	for( int i=0; i<tomato->size(); ++i ) {
		emit getTask( QTask(tomato->getTask(i)) );
	}
}
*/

void QTomato::start( void )
{
	remainingTime = totalTime;
	if( remainingTime > 0 ) {
		emit changeTime( remainingTime-restTime );
		timer->start( 1000 );
		tomato->start( workTime, restTime);
	}
}

void QTomato::timeout( void )
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
	emit changeTime( tmp );
	timer->start( 1000 );
}
