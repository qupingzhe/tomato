#include "task_widget.h"
#include "time_dialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

GroupTask::GroupTask( QTask qtask, TaskWidget* parent )
{
	id = qtask.id;
	this->parent = parent;
	taskName = new QLabel( qtask.name );
	finishTaskCheck = new QCheckBox;
	chooseTaskCheck = new QCheckBox;

	addWidget( finishTaskCheck );
	addWidget( taskName );
	addWidget( chooseTaskCheck );

	connect( finishTaskCheck, SIGNAL(stateChanged(int)),
			this, SLOT(finishTask(int)) );
	connect( chooseTaskCheck, SIGNAL(stateChanged(int)),
			this, SLOT(chooseTask(int)) );
}

GroupTask::~GroupTask( void )
{
	id = 0;
	delete taskName;
	delete finishTaskCheck;
	delete chooseTaskCheck;
}

void GroupTask::finishTask( int state )
{
	if( state == Qt::Checked ) {
		parent->finishChildTask( id );
	}
}

void GroupTask::chooseTask( int state )
{
	if( state == Qt::Checked ) {
		parent->chooseChildTask( id );
	}
}



TaskWidget::TaskWidget( void )
{
	workingTime = new QSpinBox;
	workingTime->setValue( 25 );
	restingTime = new QSpinBox;
	restingTime->setValue( 5 );
	
	startButton = new QPushButton( tr("start") );
	connect( startButton, SIGNAL(clicked()),
			this, SLOT(doStart()) );
	midLayout = new QVBoxLayout;
	midLayout->addWidget( workingTime );
	midLayout->addWidget( restingTime );
	midLayout->addWidget( startButton );

	leftLayout = new QVBoxLayout;
	leftLayout->addWidget( new QLabel(tr("fasdfasdfasdfadsf")) );
	QTask taskTmp;
	taskTmp.name = QString( "AAAA" );
	GroupTask* tmp = new GroupTask( taskTmp, this );
	leftLayout->addLayout( tmp );

	mainLayout = new QHBoxLayout;
	mainLayout->addLayout( leftLayout );
	mainLayout->addLayout( midLayout );
	setLayout( mainLayout );
}

TaskWidget::~TaskWidget( void )
{
	delete midLayout;
	delete leftLayout;
	delete mainLayout;

	delete startButton;
	delete restingTime;
	delete workingTime;
	taskGroup.clear();
	taskList.clear();
}

void TaskWidget::finishChildTask( int id )
{
	emit finishTask( id );
}

void TaskWidget::chooseChildTask( int id )
{
	emit chooseTask( id );
}

void TaskWidget::getTask( QTask qtask )
{
	int id = qtask.id;
	taskList[id] = qtask;
	GroupTask* gTask = new GroupTask( qtask, this );
	taskGroup.push_back( gTask );
	leftLayout->addLayout( gTask );
	show();
}

void TaskWidget::doStart( void )
{
	emit start();
}
