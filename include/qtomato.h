#ifndef TOMATO_QTOMATO_H
#define TOMATO_QTOMATO_H


#include <QObject>
#include <QString>

#include "qtask.h"
#include "tomato.h"

class QTimer;

namespace tomato {

class QTomato : public QObject
{
	Q_OBJECT
public:
	QTomato();
	~QTomato();
	void Load();
	void Flush();
	void FlushTask();
	void FlushDataTime();
signals:
	void UpdateTask(QTask qtask);
	void UpdateTask(const std::vector<QTask>& tasks);
	void UpdateDataTime(const std::vector<QDataTime>& data_times);
public slots:
	void AddTask(QTask qtask);
	void ChooseTask(int id, bool status);
	void FinishTask(int id, bool status);

	void Start(int work_time, int rest_time);
	void End(void);
private:
	Tomato* tomato_;
	std::vector<QTask> tasks_;
	std::vector<QDataTime> data_times_;
};

}

#endif
