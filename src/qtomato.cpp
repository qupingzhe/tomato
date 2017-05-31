#include "qtomato.h"

#include <iostream>

QTomato::QTomato( void )
{
	tomato = new Tomato();
	tasksID.clear();
}

QTomato::~QTomato( void )
{
	delete tomato;
}

void QTomato::load( void )
{
	tomato->load();
	flush();
}

void QTomato::flush( void )
{
	tasksID.clear();
	tasks.clear();
	tomato->getAllTask( tasksID );
	for( std::vector<int>::iterator i=tasksID.begin(); i != tasksID.end(); ++i ) {
		Task tmp = tomato->getTask( *i );
		tasks.push_back( QTask(tmp) );
	}
	emit updateTask( tasks );
}

void QTomato::start( int workingTime, int restingTime )
{
	tomato->start( workingTime, restingTime );
}

void QTomato::end( void )
{
	tomato->end();
	this->flush();
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
	tomato->finishTask( id );
	emit updateTask( QTask(tomato->getTask(id)) );
}

void QTomato::getTaskData( std::vector<QTaskData>& qtaskDatas )
{
	tomato->getTaskData( taskDatas );
	for( std::vector<TaskData>::iterator i=taskDatas.begin(); i!=taskDatas.end(); ++i ) {
	//for( int i=0; i<taskDatas.size(); ++i ) {
		qtaskDatas.push_back( QTaskData(*i) );
	}
}

