#include "task.h"

int BasicTask::ID = 0;

void BasicTask::init( const int& id, const int& usingTime, const int& needingTime,
		   const bool& choosed, const bool& finished )
{
	this->id = id;
	this->usingTime = usingTime;
	this->needingTime = needingTime;
	this->choosed = choosed;
	this->finished = finished;
	this->flag = 0;
}


BasicTask::BasicTask( void )
{
	init( 0, 0, 1, false, false );
}

BasicTask::BasicTask( int id, int usingTime, int needingTime, bool choosed, bool finished )
{
	init( id, usingTime, needingTime, choosed, finished );
}

BasicTask::BasicTask( const BasicTask& task )
{
	init( task.id, task.usingTime, task.needingTime, task.choosed, task.finished );
}




Task::Task( void ) : BasicTask( 0, 0, 1, false, false )
{
	;
}

Task::Task( std::wstring tag, std::wstring name, int needingTime )
			: BasicTask( 0, 0, needingTime, false, false ), tag(tag), name(name)
{
	;
}

Task::Task( BasicTask task )
{
	init( task.id, task.usingTime, task.needingTime, task.choosed, task.finished );
}

std::wistream& operator>>( std::wistream& in, Task& task )
{
	wchar_t tmp;
	in >> tmp >> task.usingTime >> task.needingTime;
	in >> task.tag >> task.name >> task.flag;
	if( tmp == L'#' ) {
		task.finished = true;
	}
	else {
		task.finished = false;
	}
	return in;
}

std::wostream& operator<<( std::wostream& out, const Task& task )
{
	wchar_t tmp;
	if( task.finished ) {
		tmp = L'#';
	}
	else if( task.usingTime < task.needingTime ) {
		tmp = L'-';
	}
	else if( task.usingTime == task.needingTime ) {
		tmp = L'=';
	}
	else if( task.usingTime > task.needingTime ) {
		tmp = L'+';
	}
	else {
		tmp = L'E';
		//error
	}
	out << tmp << " " << task.usingTime << " " << task.needingTime << " ";
	out << task.tag << " " << task.name << " " << task.flag;
	return out;
}
