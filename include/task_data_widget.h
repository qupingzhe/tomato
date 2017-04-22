#ifndef TASK_DATA_WIDGET_H
#define TASK_DATA_WIDGET_H

#include <QWidget>

#include "qtask.h"
#include <vector>

class TaskDataWidget : public QWidget
{
	Q_OBJECT
public:
	TaskDataWidget( QWidget* parent = NULL );
	void load();
signals:
	void getTaskData( std::vector<QTaskData>& qtaskDatas );
protected:
	void paintEvent( QPaintEvent* event );
private:
	Qt::GlobalColor getColor( QString color );
	std::vector<QTaskData> qtaskDatas;
};

#endif
