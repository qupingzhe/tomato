
#ifndef TASK_H
#define TASK_H

#include <string>

/*
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

class BasicTaskData
{
public:
  BasicTaskData( void ){};
  BasicTaskData( const BasicTaskData& taskData );
  int dayOffset;
  int startMinute;
  int endMinute;
};

class TaskData : public BasicTaskData
{
public:
  TaskData( void ){}
  TaskData( BasicTaskData task );
  std::wstring tag;
};
*/


namespace tomato {

//static int ID;

struct BasicTask {
  BasicTask();
  void Initialize(const int needing_time);
  friend std::wistream& operator>>(std::wistream& in, BasicTask& basic_task);
  friend std::wostream& operator<<(std::wostream& out, const BasicTask& basic_task);

  int id;
  int using_time;
  int needing_time;
  bool choosed;
  bool finished;
  time_t creating_time;
  time_t finishing_time;
};

struct Task {
  Task();
  void Initialize(const std::wstring& tag, const std::wstring& name,
                  const int needing_time = 1);

  friend std::wistream& operator>>(std::wistream& in, Task& task);
  friend std::wostream& operator<<(std::wostream& out, const Task& task);

  BasicTask basic_task;
  std::wstring tag;
  std::wstring name;
};

struct BasicDataTime {
  int day_offset;
  int start_minute;
  int end_minute;
};

struct DataTime {
  //Time(std::wstring tag, std::wstring name, int dayOffset, 
  BasicDataTime basic_data_time;
  std::wstring tag;
  std::wstring name;
};

struct Data {
  //Data(const std::wstring& tag, const std::wstring& name, const int work_time,
       //const int rest_time, const int flag = 0);
  void Initialize(const std::wstring& tag, const std::wstring& name,
                  const int work_time = 25, const int rest_time = 5,
                  const int flag = 0);

  static DataTime ToDataTime(const time_t now, const Data& data) {
      DataTime result;
      if (now < data.start_time) {
          result.basic_data_time.day_offset = -1;
          return result;
      }
      tm* tmp = localtime(&data.start_time);
      result.basic_data_time.start_minute = tmp->tm_hour * 60 + tmp->tm_min;
      result.basic_data_time.end_minute = result.basic_data_time.start_minute
                                          + data.work_time + data.rest_time;
      result.basic_data_time.day_offset = now/86400 - data.start_time/86400;
      result.tag = data.tag;
      result.name = data.name;
      return result;
  }

  friend std::wistream& operator>>(std::wistream& in, Data& data);
  friend std::wostream& operator<<(std::wostream& out, const Data& data);

  std::wstring tag;
  std::wstring name;
  int work_time;
  int rest_time;
  int flag;
  time_t start_time;
};

}

#endif

