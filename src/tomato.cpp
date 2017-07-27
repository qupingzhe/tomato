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
	SaveTask();
  SaveData();

	tasks_.clear();
  datas_.clear();
	data_times_.clear();

}

void Tomato::Load() {
  LoadTask();
  LoadData();
}


void Tomato::Start(int work_time, int rest_time) {
	//std::wofstream wout;
	//wout.open(DATA_PATH, std::ios::app);
  
  Data tmp;
	for (std::map<int,Task>::iterator i = tasks_.begin(); i != tasks_.end(); ++i) {
		if ((i->second).basic_task.choosed) {
      tmp.Initialize((i->second).tag, (i->second).name, work_time, rest_time);
      datas_.push_back(tmp);
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

void Tomato::End() {
	for (std::map<int,Task>::iterator i = tasks_.begin(); i != tasks_.end(); ++i) {
		if ((i->second).basic_task.choosed && !(i->second).basic_task.finished ) {
			(i->second).basic_task.using_time++;
		}
		(i->second).basic_task.choosed = false;
	}
	SaveTask();
  SaveData();
  FlushDataTime();
}

void Tomato::ChooseTask(int id, bool status) {
  if (HasTask(id)) {
    tasks_[id].basic_task.choosed = status;
  }
}

void Tomato::FinishTask(int id, bool status) {
  if (HasTask(id)) {
    tasks_[id].basic_task.finished = status;
  }
}


bool Tomato::HasTask(int id) {
  return (tasks_.find(id) != tasks_.end());
}

int Tomato::AddTask(Task task) {
	task.basic_task.id = ++TASK_ID;
	tasks_[task.basic_task.id] = task;
	return task.basic_task.id;
}

Task Tomato::GetTask(int id) {
  if (HasTask(id)) {
    return tasks_[id];
  }
  return Task();
}


void Tomato::LoadTask() {
	std::wifstream win;
	//win.imbue(std::locale("zh_CN.UTF-8"));
	win.open(TASK_PATH, std::ios::in);
	Task tmp;
	while (win >> tmp) {
		AddTask(tmp);
	}
	//win.imbue(std::locale("C"));
	win.close();
}

void Tomato::SaveTask() {
	std::wofstream wout;
	wout.open(TASK_PATH, std::ios::out);
	for (std::map<int,Task>::iterator i = tasks_.begin(); i != tasks_.end(); ++i) {
		wout << i->second << std::endl;
	}
	wout.close();
}

std::map<int,Task>::const_iterator Tomato::BeginForTask() {
  return tasks_.begin();
}

std::map<int,Task>::const_iterator Tomato::EndForTask() {
  return tasks_.end();
}


void Tomato::LoadData() {
  std::wifstream win;
  win.open(DATA_PATH, std::ios::in);
  Data tmp;
  while (win >> tmp) {
    datas_.push_back(tmp);
  }
}

void Tomato::SaveData() {
  std::wofstream wout;
  wout.open(DATA_PATH, std::ios::out);
  for (std::vector<Data>::iterator i = datas_.begin(); i != datas_.end(); ++i) {
    wout << *i << std::endl;
  }
}


std::vector<DataTime>::const_iterator Tomato::BeginForDataTime() {
  return data_times_.begin();
}

std::vector<DataTime>::const_iterator Tomato::EndForDataTime() {
  return data_times_.end();
}

void Tomato::FlushDataTime() {
  data_times_.clear();

  time_t now = time(NULL);
	DataTime result;
  for (std::vector<Data>::iterator i = datas_.begin(); i != datas_.end(); ++i) {
    result = Data::ToDataTime(now, *i);
    if (result.basic_data_time.day_offset > -1) {
        data_times_.push_back(result);
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
