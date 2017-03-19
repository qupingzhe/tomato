#include "tomato.h"

#include <ctime>
#include <iomanip>

Tomato::Tomato( void )
{
}

Tomato::~Tomato( void )
{
	std::wcout << L"~Tomato" << std::endl;
	std::wofstream wout;
	wout.imbue( std::locale( "zh_CN.UTF-8" ) );
	wout.open( "./task/today.task", std::ios::out );
	for( std::map<int, Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		//std::wcout << i->second << std::endl;
		
		wout << i->second << std::endl;
	}
	tasks.clear();
}

int Tomato::addTask( Task task )
{
	task.id = ++Task::ID;
	tasks[task.id] = task;
	std::wcout << task << std::endl;
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

void Tomato::usingATime( int id )
{
	tasks[id].usingTime++;
	//std::wcout << L"啊啊啊啊啊啊啊啊啊啊" << std::endl;
}

int Tomato::taskNumber( void )
{
	return tasks.size();
}

bool Tomato::isChoosed( int id )
{
	return tasks[id].choosed;
}
