#ifndef TOMATO_H
#define TOMATO_H

#include <map>
#include <vector>
#include "task.h"

class Tomato
{
public:
	Tomato( void );
	~Tomato( void );
	void load( void );

	int addTask( Task task );
	Task getTask( int id );
	std::map<int,Task>::const_iterator beginForTask() {
		return tasks.begin();
	}
	std::map<int,Task>::const_iterator endForTask() {
		return tasks.end();
	}

	std::vector<TaskData>::const_iterator beginForTaskData( void ) {
		return taskDatas.begin();
	}
	std::vector<TaskData>::const_iterator endForTaskData( void ) {
		return taskDatas.end();
	}

	void flushTaskData( int dayOffset = 7 );
	void flushTask( void );

	void chooseTask( int id, bool status );
	void finishTask( int id, bool status );
	void start( int woringTime, int restingTime );
	void end( void );
private:
	bool isIncludeDays( tm* old, tm* now, int dayOffset, TaskData* result );
	std::map<int, Task> tasks;
	std::vector<TaskData> taskDatas;
};

#endif
