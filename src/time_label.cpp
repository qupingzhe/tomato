#include "time_label.h"

#include <QTimer>

TimeLabel::TimeLabel( int mins, QWidget* parent ) : QLabel( parent )
{
	seconds = mins*60;
	this->mins = mins;
	timer = new QTimer;

	connect( timer, SIGNAL(timeout()),
			this, SLOT(updateTime()) );
	setText( getTime() );
	setScaledContents( true );
}

TimeLabel::~TimeLabel( void )
{
	delete timer;
}

void TimeLabel::restart( void )
{
	seconds = mins*60;
	updateTime();
}

void TimeLabel::updateTime( void )
{
	setText( getTime() );
	seconds--;
	if( seconds < 0 ) {
		timer->stop();
		emit timeout();
		return ;
	}
	timer->start( 1000 );
	show();
}

QString TimeLabel::getTime( void )
{
	int s_min = seconds/60;
	int s_sec1 = (seconds%60)/10;
	int s_sec2 = (seconds%60)%10;
	
	return QString( "%1:%2%3" )
			.arg( s_min )
			.arg( s_sec1 )
			.arg( s_sec2 );
}

