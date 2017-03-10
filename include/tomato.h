#ifndef TOMATO_H
#define TOMATO_H

#include <string>
#include <map>

struct Task
{
	int id;
	std::wstring classification;
	std::wstring tag;
	std::wstring name;
	int needingTime;
	bool choosed;
	bool finished;
};

class Tomato
{
public:
	static int ID;
	Tomato( void );
	~Tomato( void );

	int addTask( Task task );
	//void removeTask();
	Task getTask( int id );

	void chooseTask( int id );
	void finishTask( int id );
	void start( void );

private:
	std::map<int,Task> tasks;
};

#endif
