#include "tomato_clock.h"
#include "time_label.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QDialog>

TomatoClock::TomatoClock( QWidget* parent ) : QWidget( parent )
{
	dialog = new QDialog;
	timeInDialog = new TimeLabel( 5 );
	QLayout* layout = new QVBoxLayout;
	layout->addWidget( timeInDialog );
	dialog->setLayout( layout );
	dialog->setWindowFlags(Qt::Dialog);
	dialog->setModal( true );
	QFont font;
	font.setPointSize( 30 );
	timeInDialog->setFont( font );

	timeLabel = new TimeLabel( 25 );
	startButton = new QPushButton( tr("start") );
	mainLayout = new QVBoxLayout;
	mainLayout->addWidget( timeLabel );
	mainLayout->addWidget( startButton );
	setLayout( mainLayout );

	connect( startButton, SIGNAL(clicked()),
			timeLabel, SLOT(restart()) );
	connect( startButton, SIGNAL(clicked()),
			this, SLOT(doStart()) );

	connect( timeLabel, SIGNAL(timeout()),
			this, SLOT(rest()) );
	connect( timeInDialog, SIGNAL(timeout()),
			this, SLOT(work()) );



}

TomatoClock::~TomatoClock( void )
{
	delete startButton;
	delete mainLayout;
}

void TomatoClock::rest( void )
{
	dialog->showFullScreen();
	timeInDialog->restart();
	dialog->exec();
}

void TomatoClock::work( void )
{
	dialog->hide();
}

void TomatoClock::doStart( void )
{
	emit start();
}
