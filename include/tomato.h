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
	void Load();

	void Start(int work_time, int rest_time);
	void End();
	void ChooseTask(int id, bool status);
	void FinishTask(int id, bool status);

  bool HasTask(int id);
	int AddTask(Task task);
	Task GetTask(int id);

  void LoadTask();
	void SaveTask();
	std::map<int,Task>::const_iterator BeginForTask();
	std::map<int,Task>::const_iterator EndForTask();

  void LoadData();
	void SaveData();

	std::vector<DataTime>::const_iterator BeginForDataTime();
	std::vector<DataTime>::const_iterator EndForDataTime();
  void FlushDataTime();

private:
	//bool isIncludeDays(tm* old, tm* now, int dayOffset, TaskData* result);
	std::map<int, Task> tasks_;
	std::vector<DataTime> data_times_;
  std::vector<Data> datas_;
};

}

#endif
