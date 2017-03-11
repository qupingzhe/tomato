#include "time_dialog.h"
#include <QLabel>
#include <QHBoxLayout>

TimeDialog::TimeDialog( void )
{
	layout = new QHBoxLayout;
	label = new QLabel();
	layout->addWidget( label );
	setLayout( layout );

}

TimeDialog::~TimeDialog( void )
{
	delete layout;
	delete label;
}

void TimeDialog::changeTime( int time )
{
	label->setText( timeToString(time) );
	label->show();
}

