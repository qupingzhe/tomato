#include "tomato.h"

#include <iostream>
#include <fstream>

int Tomato::ID = 0;

Tomato::Tomato( void )
{
}

Tomato::~Tomato( void )
{

}

int Tomato::addTask( Task task )
{
	task.id = ++ID;
	std::wcout << "Task	" << task.id << task.name << std::endl;
	tasks[task.id] = task;
	return task.id;
}

Task Tomato::getTask( int id )
{
	return tasks[id];
}

void Tomato::chooseTask( int id )
{
	tasks[id].choosed = true;
}

void Tomato::finishTask( int id )
{
	tasks[id].finished= true;
}

void Tomato::start( void )
{
	std::wofstream wout;
	wout.imbue( std::locale( "zh_CN.UTF-8" ) );
	wout.open( "./date/date.bak", std::ios::app );
	for( std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed ) {
			wout << (i->second).name << std::endl;
		}
	}
}
