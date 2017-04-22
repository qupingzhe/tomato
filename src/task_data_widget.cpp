#include "task_data_widget.h"
#include <QPainter>

#include <iostream>

TaskDataWidget::TaskDataWidget( QWidget* parent ) : QWidget( parent )
{
}

void TaskDataWidget::load( void )
{
	emit getTaskData( qtaskDatas );
}

void TaskDataWidget::paintEvent( QPaintEvent* event )
{
	//emit getTaskData( qtaskDatas );
	QPainter painter( this );
	painter.setPen( Qt::NoPen );
	QString noTag = QString::fromStdWString( L"空" );
	int nowDayOffset = 7;
	int nowMinute = 0;
	for( int i=0; i<qtaskDatas.size(); ++i ) {
		if( nowDayOffset != qtaskDatas[i].dayOffset || nowMinute != qtaskDatas[i].startMinute ) {
			painter.setBrush( QBrush(getColor(noTag),Qt::SolidPattern) );
			while( true ) {
				if( nowDayOffset == qtaskDatas[i].dayOffset
						&& nowMinute == qtaskDatas[i].startMinute ) {
					break;
				}
				painter.drawRect( nowMinute, (7 - nowDayOffset)*50, 1, 20 );
				nowMinute++;
				int ans = nowMinute/900;
				nowMinute %= 900;
				nowDayOffset -= ans;
			}
		}
		painter.setBrush( QBrush(getColor( qtaskDatas[i].tag ),Qt::SolidPattern) );
		for( ; nowMinute < qtaskDatas[i].endMinute; ++nowMinute ) {
			painter.drawRect( nowMinute, (7-nowDayOffset)*50, 1, 20 );
		}

	}
	int endDayOffset = 0;
	int endMinute = 900;
	painter.setBrush( QBrush(getColor(noTag), Qt::SolidPattern) );
	while( true ) {
		if( nowDayOffset < 0 ) {
			break;
		}
		if( nowDayOffset == endDayOffset && nowMinute == endMinute ) {
			break;
		}
		painter.drawRect( nowMinute, (7-nowDayOffset)*50, 1, 20 );
		nowMinute++;
		int ans = nowMinute/900;
		nowMinute %= 900;
		nowDayOffset -= ans;
	}
}

Qt::GlobalColor TaskDataWidget::getColor( QString tag )
{
	static const QString book = QString::fromStdWString( L"看书" );
	static const QString blog = QString::fromStdWString( L"博客" );
	static const QString project = QString::fromStdWString( L"项目" );
	static const QString algorithm = QString::fromStdWString( L"算法" );
	static const QString homework = QString::fromStdWString( L"作业" );
	static const QString school = QString::fromStdWString( L"课堂" );
	Qt::GlobalColor value;
	if( tag ==  book ) {
		value = Qt::blue;
	} else if( tag ==  blog) {
		value = Qt::green;
	} else if( tag ==  project ) {
		value = Qt::red;
	} else if( tag == algorithm ) {
		value = Qt::yellow;
	} else if( tag ==  homework) {
		value = Qt::white;
	} else if( tag == school ) {
		value = Qt::cyan;
	} else {
		value = Qt::black;
	}
	return value;
}

