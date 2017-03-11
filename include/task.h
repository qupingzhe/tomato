#ifndef TASK_H
#define TASK_H

#include <string>
#include <fstream>
#include <iostream>

class BasicTask
{
public:
	static int ID;
	BasicTask( void );
	BasicTask( int id, int usingTime, int needingTime, bool choosed, bool finished );
	BasicTask( const  BasicTask& task );
	void init( const int& id, const int& usingTime, const int& needingTime,
			   const bool& choosed, const bool& finished );

	int id;
	int usingTime;
	int needingTime;
	bool choosed;
	bool finished;
	int flag;
};


class Task : public BasicTask
{
public:
	Task( void );
	Task( std::wstring tag, std::wstring name, int needingTime );
	Task( BasicTask task );
	friend std::wistream& operator>>( std::wistream& in, Task& task );
	friend std::wostream& operator<<( std::wostream& out, const Task& task );

	std::wstring tag;
	std::wstring name;
};

#endif