#ifndef TOMATO_TIME_H
#define TOMATO_TIME_H

#include <QObject>

class QTimer;

namespace tomato {

class Timer : public QObject {
	Q_OBJECT
public:
	Timer();
	~Timer();
	void SetTimer(int workTime, int restTime);
signals:
	void FinishWork();
	void FinishRest();
	void DisplayTime( int time );
public slots:
	void Start();
private slots:
	void Timeout();
private:
	QTimer* timer_;
	int remaining_time_;
	int rest_time_;
	int work_time_;
};

}

#endif
