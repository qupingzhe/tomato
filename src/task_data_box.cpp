#include "task_data_widget.h"
//#include "task_data_box.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

/*
void TaskDataCanvas::drawInCanvas( int offset, QColor color )
{
	QPainter painter( this );
	painter.setPen( Qt::NoPen );
	painter.setBrush( QBrush(color) );
	painter.drawRect( offset, 0, 1, 20 );
}
*/

TaskDataCanvas::TaskDataCanvas( QWidget* parent ) : QWidget(parent)
{
	setMinimumWidth( 900 );
	//setMinimumWidth( 90 );
}

void TaskDataCanvas::paintEvent( QPaintEvent* event )
{
	//emit getTaskData( qtaskDatas );
	int utilizationMinutes = 0;
	QPainter painter( this );
	painter.setPen( Qt::NoPen );

	QString noTag = QString::fromStdWString( L"空" );

	int nowMinute = 0;
	for( std::vector<QTaskData>::iterator i=qtaskDatas.begin();
			i != qtaskDatas.end(); ++i ) {
		if( nowMinute != i->startMinute ) {
			painter.setBrush( QBrush(TaskDataWidget::getColor(noTag),Qt::SolidPattern) );
			while( true ) {
				if( nowMinute >= i->startMinute ) {
					break;
				}
				painter.drawRect( nowMinute, 0, 1, 20 );
				nowMinute++;
				nowMinute %= 900;
				if( nowMinute == 0 ) {
					break;
				}
			}
		}
    	painter.setBrush( QBrush(TaskDataWidget::getColor( i->tag ), Qt::SolidPattern) );
		for( ; nowMinute < i->endMinute; ++nowMinute ) {
			utilizationMinutes++;
			painter.drawRect( nowMinute, 0, 1, 20 );
		}

	}
	int endMinute = 900;
    painter.setBrush( QBrush(TaskDataWidget::getColor(noTag), Qt::SolidPattern) );
	while( true ) {
		if( nowMinute >= endMinute ) {
			break;
		}
		painter.drawRect( nowMinute, 0, 1, 20 );
		nowMinute++;
		nowMinute %= 900;
		if( nowMinute == 0 ) {
			break;
		}
	}
	emit changedUtilizationRate(utilizationMinutes*100/900);
}

std::vector<QTaskData>& TaskDataCanvas::getTaskDatas( void )
{
	return this->qtaskDatas;
}

QColor TaskDataBox::NO_USING_COLOR = QColor(Qt::black);

TaskDataBox::TaskDataBox( int dayOffset, QWidget* parent ) : QWidget( parent )
{
	dayOffsetLabel = new QLabel( QString("%1").arg(dayOffset ) );
	utilizationRateLabel = new QLabel;
	layout = new QHBoxLayout;
	taskDataCanvas = new TaskDataCanvas;

	utilizationTime = 0;
	allTime = 0;

	connect( taskDataCanvas, SIGNAL(changedUtilizationRate(int)),
			this, SLOT(utilizationRate(int)) );

	layout->addWidget( dayOffsetLabel );
	layout->addWidget( taskDataCanvas );
	layout->addWidget( utilizationRateLabel );
	setLayout( layout );
}

TaskDataBox::~TaskDataBox( void )
{
	delete taskDataCanvas;
	delete utilizationRateLabel;
	delete layout;
}

std::vector<QTaskData>& TaskDataBox::getTaskDatas( void )
{
	return taskDataCanvas->getTaskDatas();
}

void TaskDataBox::utilizationRate(int rate)
{
	utilizationRateLabel->setText( QString("%1%").arg(rate));
}


/*
void TaskDataBox::drawTaskData( int minutes, QColor color )
{
	if( color != NO_USING_COLOR ) {
		utilizationTime++;
	}
	allTime++;
	utilizationRateLabel->setText( QString("%1%%").arg(utilizationTime*100/allTime) );
	taskDataCanvas->drawInCanvas( minutes, color );
}
*/
