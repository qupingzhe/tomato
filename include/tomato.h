#ifndef TOMATO_H
#define TOMATO_H

#include <map>
#include <vector>
#include "task.h"

namespace tomato {

class Tomato {
public:
	Tomato();
	~Tomato();
	void load();

	void start(int work_time, int rest_time);
	void end();
	void chooseTask(int id, bool status);
	void finishTask(int id, bool status);

  bool hasTask(int id);
	int addTask(Task task);
	Task getTask(int id);

  void loadTask();
	void saveTask();
	std::map<int,Task>::const_iterator beginForTask();
	std::map<int,Task>::const_iterator endForTask();

  void loadData();
	void saveData();

	std::vector<DataTime>::const_iterator beginForDataTime();
	std::vector<DataTime>::const_iterator endForDataTime();
  void flushDataTime();

private:
	//bool isIncludeDays(tm* old, tm* now, int dayOffset, TaskData* result);
	std::map<int, Task> tasks;
	std::vector<DataTime> data_times;
  std::vector<Data> datas;
};

}

#endif
