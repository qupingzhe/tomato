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
	void getAllTask( std::vector<int>& tasksID );

	void chooseTask( int id );
	void finishTask( int id );
	void start( int woringTime, int restingTime );
	void end( void );

	bool isChoosed( int id );
	void getTaskData( std::vector<TaskData>& taskDatas, int dayOffset = 7 );
private:
	bool isIncludeDays( tm* old, tm* now, int dayOffset, TaskData* result );
	std::map<int,Task> tasks;
};

#endif
