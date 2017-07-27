#include "tomato.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>

namespace tomato {
//static int DAYS[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

static const char TASK_PATH[] = "test.task";
static const char DATA_PATH[] = "test.data";

static int TASK_ID = 0;

Tomato::Tomato() {
}

Tomato::~Tomato() {
	saveTask();
  saveData();

	tasks.clear();
  datas.clear();
	data_times.clear();

}

void Tomato::load() {
  loadTask();
  loadData();
}


void Tomato::start(int work_time, int rest_time) {
	//std::wofstream wout;
	//wout.open(DATA_PATH, std::ios::app);
  
  Data tmp;
	for (std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i) {
		if ((i->second).choosed) {
      tmp.Initialize((i->second).tag, (i->second).name, work_time, rest_time);
      datas.push_back(tmp);
      //wout << tmp << std::endl;

      /*
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
      */
		}
	}
	//wout.close();
}

void Tomato::end() {
	for (std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i) {
		if ((i->second).choosed && !(i->second).finished ) {
			(i->second).using_time++;
		}
		(i->second).choosed = false;
	}
	saveTask();
  saveData();
  flushDataTime();
}

void Tomato::chooseTask(int id, bool status) {
  if (hasTask(id)) {
    tasks[id].choosed = status;
  }
}

void Tomato::finishTask(int id, bool status) {
  if (hasTask(id)) {
    tasks[id].finished = status;
  }
}


bool Tomato::hasTask(int id) {
  return (tasks.find(id) != tasks.end());
}

int Tomato::addTask(Task task) {
	task.id = ++TASK_ID;
	tasks[task.id] = task;
	return task.id;
}

Task Tomato::getTask(int id) {
  if (hasTask(id)) {
    return tasks[id];
  }
  return Task();
}


void Tomato::loadTask() {
	std::wifstream win;
	//win.imbue(std::locale("zh_CN.UTF-8"));
	win.open(TASK_PATH, std::ios::in);
	Task tmp;
	while (win >> tmp) {
		addTask(tmp);
	}
	//win.imbue(std::locale("C"));
	win.close();
}

void Tomato::saveTask() {
	std::wofstream wout;
	wout.open(TASK_PATH, std::ios::out);
	for (std::map<int,Task>::iterator i = tasks.begin(); i != tasks.end(); ++i) {
		wout << i->second << std::endl;
	}
	wout.close();
}

std::map<int,Task>::const_iterator Tomato::beginForTask() {
  return tasks.begin();
}

std::map<int,Task>::const_iterator Tomato::endForTask() {
  return tasks.end();
}


void Tomato::loadData() {
  std::wifstream win;
  win.open(DATA_PATH, std::ios::in);
  Data tmp;
  while (win >> tmp) {
    datas.push_back(tmp);
  }
}

void Tomato::saveData() {
  std::wofstream wout;
  wout.open(DATA_PATH, std::ios::out);
  for (std::vector<Data>::iterator i = datas.begin(); i != datas.end(); ++i) {
    wout << *i << std::endl;
  }
}


std::vector<DataTime>::const_iterator Tomato::beginForDataTime() {
  return data_times.begin();
}

std::vector<DataTime>::const_iterator Tomato::endForDataTime() {
  return data_times.end();
}

void Tomato::flushDataTime() {
  data_times.clear();

  time_t now = time(NULL);
	DataTime result;
  for (std::vector<Data>::iterator i = datas.begin(); i != datas.end(); ++i) {
    result = Data::toDataTime(now, *i);
    if (result.day_offset > -1) {
        data_times.push_back(result);
    }
  }
}


/*
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
*/

}
