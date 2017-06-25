#include "tomato.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

static int DAYS[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static const char TASK_PATH[] = "task/task";
static const char DATA_PATH[] = "data/data";

Tomato::Tomato( void )
{
}

Tomato::~Tomato( void )
{
	flushTask();
	tasks.clear();
	taskDatas.clear();
}

void Tomato::load( void )
{
	std::wifstream win;
	win.imbue( std::locale( "zh_CN.UTF-8" ) );
	win.open( TASK_PATH, std::ios::in );
	Task tmp;
	while( win >> tmp ) {
		this->addTask( tmp );
	}
	win.imbue( std::locale( "C" ) );
	win.close();
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


void Tomato::chooseTask( int id, bool status )
{
	tasks[id].choosed = status;
}

void Tomato::finishTask( int id, bool status )
{
	tasks[id].finished= status;
}

void Tomato::start( int workingTime, int restingTime )
{
	std::wofstream wout;
	wout.open( DATA_PATH, std::ios::app );

	for( std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed ) {
			timespec timeS;
			clock_gettime(CLOCK_REALTIME, &timeS);
			tm now;
			localtime_r(&timeS.tv_sec, &now);

			wout << std::setfill( L'0' ) << std::setw(4) << now.tm_year + 1900 << " ";
			wout << std::setfill( L'0' ) << std::setw(2) << now.tm_mon+1 << " ";
			wout << std::setfill( L'0' ) << std::setw(2) << now.tm_mday << " ";

			wout << std::setfill( L'0' ) << std::setw(2) << now.tm_hour << " ";
			wout << std::setfill( L'0' ) << std::setw(2) << now.tm_min << " ";

			wout << std::setfill( L'0' ) << std::setw(2) << now.tm_sec << " ";
			wout << (i->second).flag << " ";

			wout.imbue( std::locale( "zh_CN.UTF-8" ) );
			wout <<	(i->second).tag << " " << (i->second).name << " ";
			wout.imbue( std::locale("C") );

			wout << workingTime << " " << restingTime << std::endl;
		}
	}
	wout.close();
}

void Tomato::end( void )
{
	for( std::map<int, Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		if( (i->second).choosed && !(i->second).finished ) {
			(i->second).usingTime++;
		}
		(i->second).choosed = false;
	}
	flushTask();
}
	

void Tomato::flushTask( void )
{
	std::wofstream wout;
	wout.imbue( std::locale( "zh_CN.UTF-8" ) );
	wout.open( TASK_PATH, std::ios::out );
	for( std::map<int, Task>::iterator i = tasks.begin(); i != tasks.end(); ++i ) {
		wout << i->second << std::endl;
	}
	wout.close();
}

void Tomato::flushTaskData( int dayOffset )
{
	if( dayOffset > 7 ) {
		return ;
	}
	timespec timeS;
	clock_gettime( CLOCK_REALTIME, &timeS );
	tm now;
	localtime_r( &timeS.tv_sec, &now );
	now.tm_year += 1900;
	now.tm_mon++;

	tm old;
	int workTime, restTime;
	int flag;
	std::wstring tag, name;
	TaskData result;
	std::wifstream win;
	win.open( DATA_PATH, std::ios::in );
	while( win >> old.tm_year >> old.tm_mon >> old.tm_mday ) {
		win >> old.tm_hour >> old.tm_min >> old.tm_sec;
		win >> flag;
		win.imbue( std::locale( "zh_CN.UTF-8" ) );
		win >> tag >> name;
		win.imbue( std::locale("C") );

		win >> workTime >> restTime;

		if( isIncludeDays( &old, &now, dayOffset, &result ) ) {
			result.endMinute = result.startMinute + workTime + restTime;
			result.tag = tag;
			taskDatas.push_back( result );
		}
	}
	win.close();
}

bool Tomato::isIncludeDays( tm* old, tm* now, int dayOffset, TaskData* result )
{
	int ans = 0;
	for( int i=0; i<=dayOffset; ++i ) {
		if( old->tm_year == now->tm_year &&
			old->tm_mon == now->tm_mon &&
			old->tm_mday == now->tm_mday ) {
			result->dayOffset = i;
			result->startMinute = (old->tm_hour-8)*60 + old->tm_min;
			return  true;
		}
		if( old->tm_year%400 == 0 || ( old->tm_year%100 != 0 && old->tm_year%4 == 0 ) ) {
			DAYS[2] = 29;
		}
		else {
			DAYS[2] = 28;
		}
		old->tm_mday++;
		ans = old->tm_mday/(DAYS[old->tm_mon]+1);
		old->tm_mday %= (DAYS[old->tm_mon]+1);
		if( ans == 1 ) {
			old->tm_mday++;
		}
		old->tm_mon += ans;
		ans = old->tm_mon/13;
		old->tm_mon %= 13;
		if( ans == 1 ) {
			old->tm_mon++;
		}
		old->tm_year += ans;
	}
	//std::wcout << L"start------------------------" << std::endl;
	//std::wcout << old->tm_mon << " " << old->tm_mday << "	|	" << now->tm_mon << " " << now->tm_mday << std::endl;
	return false;
}
