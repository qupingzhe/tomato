#include "task.h"
#include <fstream>

/*
int BasicTask::ID = 0;

void BasicTask::init( const int& id, const int& usingTime, const int& needingTime,
       const bool& choosed, const bool& finished )
{
  this->id = id;
  this->usingTime = usingTime;
  this->needingTime = needingTime;
  this->choosed = choosed;
  this->finished = finished;
  this->flag = 0;
}


BasicTask::BasicTask( void )
{
  init( 0, 0, 1, false, false );
}

BasicTask::BasicTask( int id, int usingTime, int needingTime, bool choosed, bool finished )
{
  init( id, usingTime, needingTime, choosed, finished );
}

BasicTask::BasicTask( const BasicTask& task )
{
  init( task.id, task.usingTime, task.needingTime, task.choosed, task.finished );
}




Task::Task( void ) : BasicTask( 0, 0, 1, false, false )
{
  ;
}

Task::Task( std::wstring tag, std::wstring name, int needingTime )
      : BasicTask( 0, 0, needingTime, false, false ), tag(tag), name(name)
{
  ;
}

Task::Task( BasicTask task )
{
  init( task.id, task.usingTime, task.needingTime, task.choosed, task.finished );
}

std::wistream& operator>>( std::wistream& in, Task& task )
{
  wchar_t tmp;
  in >> tmp >> task.usingTime >> task.needingTime;
  in >> task.tag >> task.name >> task.flag;
  if( tmp == L'#' ) {
    task.finished = true;
  }
  else {
    task.finished = false;
  }
  return in;
}

std::wostream& operator<<( std::wostream& out, const Task& task )
{
  wchar_t tmp;
  if( task.finished ) {
    tmp = L'#';
  }
  else if( task.usingTime < task.needingTime ) {
    tmp = L'-';
  }
  else if( task.usingTime == task.needingTime ) {
    tmp = L'=';
  }
  else if( task.usingTime > task.needingTime ) {
    tmp = L'+';
  }
  else {
    tmp = L'E';
    //error
  }
  out << tmp << " " << task.usingTime << " " << task.needingTime << " ";
  out << task.tag << " " << task.name << " " << task.flag;
  return out;
}

BasicTaskData::BasicTaskData( const BasicTaskData& taskData )
{
  this->dayOffset = taskData.dayOffset;
  this->startMinute = taskData.startMinute;
  this->endMinute = taskData.endMinute;
}

TaskData::TaskData( BasicTaskData taskData ) : BasicTaskData(taskData)
{
}
*/

namespace tomato {

Task::Task() {
  id = -1;
  using_time = 0;
  needing_time = 1;
  choosed = false;
  finished = false;
  creating_time = 0;
  finishing_time = 0;
  tag = L"";
  name = L"";
}

void Task::Initialize(const std::wstring& tag, const std::wstring& name,
                      const int needing_time) {
  this->id = -1;
  this->using_time = 0;
  this->choosed = false;
  this->finished = false;
  this->creating_time = time(NULL);
  this->finishing_time = 0;
  this->tag = tag;
  this->name = name;
  this->needing_time = needing_time;
}

std::wistream& operator>>(std::wistream& in, Task& task) {
  wchar_t tmp;
  in >> tmp >> task.using_time >> task.needing_time;
  in >> task.creating_time >> task.finishing_time;
  in.imbue(std::locale("zh_CN.UTF-8"));
  in >> task.tag >> task.name;
  in.imbue(std::locale("C"));
  if (tmp == L'#') {
    task.finished = true;
  } else {
    task.finished = false;
  }
  return in;
}

std::wostream& operator<<(std::wostream& out, const Task& task) {
  wchar_t tmp;
  if (task.finished) {
    tmp = L'#';
  } else if (task.using_time < task.needing_time) {
    tmp = L'-';
  } else if (task.using_time > task.needing_time) {
    tmp = L'+';
  } else {
    tmp = L'=';
  }
  out << tmp << L" " << task.using_time << L" " << task.needing_time << L" ";
  out << task.creating_time << L" " << task.finishing_time << L" ";
  out.imbue(std::locale("zh_CN.UTF-8"));
  out << task.tag << L" " << task.name;
  out.imbue(std::locale("C"));
  return out;
}

/*
Data::Data(const std::wstring& tag, const std::wstring& name, const int work_time,
     const int rest_time, const int flag) : tag(tag), name(name),
     work_time(work_time), rest_time(rest_time), flag(flag) {
  start_time = time(NULL);
}
*/

void Data::Initialize(const std::wstring& tag, const std::wstring& name,
                      const int work_time, const int rest_time, const int flag) {
  this->tag = tag;
  this->name = name;
  this->work_time = work_time;
  this->rest_time = rest_time;
  this->flag = flag;
  this->start_time = time(NULL);
}

std::wistream& operator>>(std::wistream& in, Data& data) {
  in >> data.start_time >> data.work_time >> data.rest_time >> data.flag;
  in.imbue(std::locale("zh_CN.UTF-8"));
  in >> data.tag >> data.name;
  in.imbue(std::locale("C"));
  return in;
}

std::wostream& operator<<(std::wostream& out, const Data& data) {
  out << data.start_time << L" " << data.work_time << L" " << data.rest_time
      << L" " << data.flag << L" ";
  out.imbue(std::locale("zh_CN.UTF-8"));
  out << data.tag << L" " << data.name;
  out.imbue(std::locale("C"));
  return out;
}

}
