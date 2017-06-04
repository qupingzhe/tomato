#include "task_data_widget.h"
#include <QPainter>

#include <iostream>
#include <QVBoxLayout>

const int MAX_DAY_OFFSET = 7;

TaskDataWidget::TaskDataWidget( QWidget* parent ) : QWidget( parent )
{
	layout = new QVBoxLayout;
	taskDataBox = new TaskDataBox*[MAX_DAY_OFFSET+1];
	for( int i=0; i<=MAX_DAY_OFFSET; ++i ) {
		taskDataBox[i] = new TaskDataBox( i );
		layout->addWidget( taskDataBox[i] );
	}
	setLayout(layout);
}

TaskDataWidget::~TaskDataWidget( void )
{
	for( int i=0; i<=MAX_DAY_OFFSET; ++i ) {
		delete taskDataBox[i];
	}
	delete[] taskDataBox;
	delete layout;
}

void TaskDataWidget::updateTaskData( const std::vector<QTaskData>& qtaskDatas )
{
	for( int i=0; i<=MAX_DAY_OFFSET; ++i ) {
		taskDataBox[i]->getTaskDatas().clear();
	}
	for( std::vector<QTaskData>::const_iterator i = qtaskDatas.begin();
			i != qtaskDatas.end(); ++i ) {
		taskDataBox[i->dayOffset]->getTaskDatas().push_back(*i);
	}
}

