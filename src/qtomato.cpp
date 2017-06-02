#include "qtomato.h"

#include <iostream>

QTomato::QTomato( void )
{
	tomato = new Tomato();
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
	flushTask();
	flushTaskData();
}

void QTomato::flushTask( void )
{
	tasks.clear();
	for( std::map<int, Task>::const_iterator i=tomato->beginForTask();
			i != tomato->endForTask(); ++i ) {
		tasks.push_back( QTask(i->second) );
	}
	emit updateTask( tasks );
}

void QTomato::flushTaskData( void )
{
	tomato->flushTaskData();
	taskDatas.clear();
	for( std::vector<TaskData>::const_iterator i=tomato->beginForTaskData();
			i != tomato->endForTaskData(); ++i ) {
		taskDatas.push_back( QTaskData( *i ) );
	}
	emit updateTaskData( taskDatas );
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

void QTomato::chooseTask( int id, bool status )
{
	tomato->chooseTask( id, status );
	emit updateTask( QTask(tomato->getTask(id)) );
}

void QTomato::finishTask( int id, bool status )
{
	tomato->finishTask( id, status );
	emit updateTask( QTask(tomato->getTask(id)) );
}

