#include "tomato.h"

#include <ctime>
#include <iomanip>

Tomato::Tomato( void )
{
	std::wifstream win;
	win.imbue( std::locale( "zh_CN.UTF-8" ) );
	win.open( "./task/today.task", std::ios::in );
	Task tmp;
	while( win >> tmp ) {
		if( !tmp.finished ) {
			addTask( tmp );
		}
	}
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

void Tomato::chooseTask( int id )
{
	tasks[id].choosed = !tasks[id].choosed;
}

void Tomato::finishTask( int id )
{
	tasks[id].finished= true;
}

void Tomato::start( int workingTime, int restingTime )
{
	std::wofstream wout;
	wout.imbue( std::locale( "zh_CN.UTF-8" ) );
	wout.open( "./date/today.data.bak", std::ios::app );
	for( std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed ) {
			++((i->second).usingTime);

			timespec timeS;
			clock_gettime(CLOCK_REALTIME, &timeS);
			tm now;
			localtime_r(&timeS.tv_sec, &now);

			wout << now.tm_year+1900 << " " << now.tm_mon+1 << " ";
			wout << now.tm_mday << " " << now.tm_hour << " ";
			wout << now.tm_min << " " << now.tm_sec << " ";

			wout << (i->second).flag << " ";
			wout <<	(i->second).tag << " " << (i->second).name << " ";
			wout << workingTime << " " << restingTime << std::endl;
		}
	}
}
