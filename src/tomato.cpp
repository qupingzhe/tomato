#include "tomato.h"

#include <ctime>
#include <iomanip>

Tomato::Tomato( void )
{
}

Tomato::~Tomato( void )
{
	std::wofstream wout;
	wout.imbue( std::locale( "zh_CN.UTF-8" ) );
	wout.open( "./task/today.task", std::ios::out );
	for( std::map<int, Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		wout << i->second << std::endl;
	}
	tasks.clear();
}

void Tomato::load( void )
{
	std::wifstream win;
	win.imbue( std::locale( "zh_CN.UTF-8" ) );
	win.open( "./task/today.task", std::ios::in );
	Task tmp;
	while( win >> tmp ) {
		//std::wcout << tmp << std::endl;
		this->addTask( tmp );
	}
	win.imbue( std::locale( "C" ) );
}

int Tomato::addTask( Task task )
{
	task.id = ++Task::ID;
	tasks[task.id] = task;
	return task.id;
}

Task Tomato::getTask( int id )
{
	return tasks[id];
}

void Tomato::getAllTask( std::vector<int> &tasksID )
{
	for( std::map<int, Task>::iterator i = this->tasks.begin();
			i != this->tasks.end(); ++i ) {
		tasksID.push_back( (i->second).id );
	}
}

void Tomato::chooseTask( int id )
{
	tasks[id].choosed = !tasks[id].choosed;
}

void Tomato::finishTask( int id )
{
	tasks[id].finished= !tasks[id].finished;
}

void Tomato::start( int workingTime, int restingTime )
{
	std::wofstream wout;
	wout.open( "./date/today.data.bak", std::ios::app );
	for( std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed ) {
			timespec timeS;
			clock_gettime(CLOCK_REALTIME, &timeS);
			tm now;
			localtime_r(&timeS.tv_sec, &now);

			wout <<  std::setw(4) << now.tm_year + 1900 << " " << std::setw(2) << now.tm_mon+1 << " ";
			wout << std::setw(2) << now.tm_mday << " " <<  std::setw(2) << now.tm_hour << " ";
			wout << now.tm_min << " " << now.tm_sec << " ";
			wout << (i->second).flag << " ";

			wout.imbue( std::locale( "zh_CN.UTF-8" ) );
			wout <<	(i->second).tag << " " << (i->second).name << " ";
			wout.imbue( std::locale("C") );

			wout << workingTime << " " << restingTime << std::endl;
		}
	}
}

void Tomato::end( void )
{
	for( std::map<int, Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed && !(i->second).finished ) {
			(i->second).usingTime++;
		}
		(i->second).choosed = false;
	}
}
	
bool Tomato::isChoosed( int id )
{
	return tasks[id].choosed;
}

