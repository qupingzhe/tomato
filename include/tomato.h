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
	//void getAllTask( std::vector<int>& tasksID );
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

	void chooseTask( int id );
	void finishTask( int id );
	void start( int woringTime, int restingTime );
	void end( void );

	bool isChoosed( int id );
	//void getTaskData( std::vector<TaskData>& taskDatas, int dayOffset = 7 );
private:
	bool isIncludeDays( tm* old, tm* now, int dayOffset, TaskData* result );
	std::map<int, Task> tasks;
	std::vector<TaskData> taskDatas;
};

#endif
