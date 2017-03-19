#ifndef TOMATO_H
#define TOMATO_H

#include <map>
#include "task.h"

class Tomato
{
public:
	Tomato( void );
	~Tomato( void );

	int addTask( Task task );
	//void removeTask();
	Task getTask( int id );
	void usingATime( int id );

	int taskNumber( void );
	bool isChoosed( int id );

	void chooseTask( int id );
	void finishTask( int id );
	void start( int woringTime, int restingTime );

private:
	std::map<int,Task> tasks;
};

#endif
