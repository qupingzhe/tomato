#include "qtomato.h"

#include <QTimer>

//#include <iostream>

QTomato::QTomato( void )
{
	tomato = new Tomato();
	timer = new QTimer;

	connect( timer, SIGNAL(timeout()),
			this, SLOT(timeout()) );
}

QTomato::~QTomato( void )
{
	delete tomato;
	delete timer;
}

void QTomato::load( void )
{
	std::wifstream win;
	win.imbue( std::locale( "zh_CN.UTF-8" ) );
	win.open( "./task/today.task", std::ios::in );
	Task tmp;
	while( win >> tmp ) {
		//std::wcout << tmp << std::endl;
		this->addTask( QTask(tmp) );
	}
	win.imbue( std::locale( "C" ) );
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
	emit updateTask( QTask(tomato->getTask(id)) );
}

void QTomato::chooseTask( int id )
{
	tomato->chooseTask( id );
	emit updateTask( QTask(tomato->getTask(id)) );
}

void QTomato::finishTask( int id )
{
	//std::wcout << L"finish	" << id << std::endl;
	tomato->finishTask( id );
	emit updateTask( QTask(tomato->getTask(id)) );
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
		doFinishWork();
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

void QTomato::doFinishWork( void )
{
	for( int i=1; i<=tomato->taskNumber(); ++i ) {
		int id = i;
		//std::wcout << L"errrrrrr" << std::endl;
		if( tomato->isChoosed( id ) ) {
			tomato->usingATime( id );
			emit updateTask( tomato->getTask(id) );
		}
	}
	emit finishWork();
}
