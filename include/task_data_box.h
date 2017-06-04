#ifndef Task_DATA_BOX_H
#define TASK_DATA_BOX_H

#include <QWidget>

#include "qtask.h"

class QLabel;
class QHBoxLayout;

class TaskDataCanvas : public QWidget
{
	Q_OBJECT
public:
	TaskDataCanvas( QWidget* parent = NULL );
	void paintEvent( QPaintEvent* event );
	std::vector<QTaskData>& getTaskDatas( void );
signals:
	void changedUtilizationRate(int rate);
private:
	std::vector<QTaskData>qtaskDatas;
};


class TaskDataBox : public QWidget
{
	Q_OBJECT
public:
	static QColor NO_USING_COLOR;

	TaskDataBox( int dayOffset, QWidget* parent = NULL );
	~TaskDataBox( void );
	std::vector<QTaskData>& getTaskDatas( void );
private slots:
	void utilizationRate(int rate);

private:
	QLabel* dayOffsetLabel;
	QLabel* utilizationRateLabel;
	TaskDataCanvas* taskDataCanvas;

	int utilizationTime;
	int allTime;

	QHBoxLayout* layout;
};

#endif
