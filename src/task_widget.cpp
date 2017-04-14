#include "task_widget.h"
#include "task_box.h"
#include "time_dialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>

TaskWidget::TaskWidget( void )
{
	workTimeBox = new QSpinBox;
	restTimeBox = new QSpinBox;
	
	startButton = new QPushButton( tr("start") );
	connect( startButton, SIGNAL(clicked()),
			this, SLOT(doStart()) );
	connect( workTimeBox, SIGNAL(valueChanged(int)),
			this, SLOT(workTime(int)) );
	connect( restTimeBox, SIGNAL(valueChanged(int)),
			this, SLOT(restTime(int)) );

	showFinish = new QCheckBox( tr("finish?") );

	midLayout = new QVBoxLayout;
	midLayout->addStretch( 0 );
	midLayout->addWidget( workTimeBox );
	midLayout->addWidget( restTimeBox );
	midLayout->addWidget( startButton );
	midLayout->addStretch( 0 );

	leftLayout = new QVBoxLayout;

	QHBoxLayout* taskTitle = new QHBoxLayout;
	taskTitle->addWidget( showFinish );
	taskTitle->addWidget( new QLabel( tr("using") ) );
	taskTitle->addWidget( new QLabel( tr("needing") ) );
	taskTitle->addWidget( new QLabel( tr("tag") ) );
	taskTitle->addWidget( new QLabel( tr("name") ) );
	taskTitle->addWidget( new QLabel( tr("choose?") ) );

	connect( showFinish, SIGNAL(stateChanged(int)),
			this, SLOT(hideTask(int)) );
	showFinish->setCheckState( Qt::Unchecked );

	leftLayout->addStretch( 1 );
	leftLayout->addLayout( taskTitle );

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
	delete restTimeBox;
	delete workTimeBox;
	for( std::vector<TaskBox*>::iterator i = taskGroup.begin(); i != taskGroup.end(); ++i ) {
		//delete *i;
	}
	taskGroup.clear();
}

void TaskWidget::load( void )
{
	workTimeBox->setValue( 25 );
	restTimeBox->setValue( 5 );
}

void TaskWidget::finishChildTask( int id, bool flag )
{
	emit finishTask( id );
}

void TaskWidget::chooseChildTask( int id, bool flag )
{
	emit chooseTask( id );
}

void TaskWidget::updateTask( QTask qtask )
{
	size_t ptr = 0;
	size_t taskNumber = taskGroup.size();
	for( ; ptr < taskNumber; ++ptr ) {
		if( taskGroup[ptr]->getID() == qtask.id ) {
			break;
		}
	}
	if( ptr == taskNumber ) {
		TaskBox* tmp = new TaskBox( qtask, showFinish->checkState(), this );
		taskGroup.push_back( tmp );
		leftLayout->addLayout( tmp );
	}
	else {
		taskGroup[ptr]->updateTask( qtask );
		taskGroup[ptr]->updateDisplay();
	}
}

void TaskWidget::updateTask( std::vector<QTask> &qtasks )
{
	for( std::vector<QTask>::iterator i=qtasks.begin(); i != qtasks.end(); ++i ) {
		this->updateTask( *i );
	}
}

void TaskWidget::doStart( void )
{
	emit start();
}

void TaskWidget::hideTask( int state )
{
	bool isHidingTask = state==Qt::Checked?false:true;
	for( std::vector<TaskBox*>::iterator i=taskGroup.begin(); i != taskGroup.end(); ++i ) {
		(*i)->setHidingState( isHidingTask );
	}
}

void TaskWidget::workTime( int minutes )
{
	emit workTimeChanged( minutes );
}

void TaskWidget::restTime( int minutes )
{
	emit restTimeChanged( minutes );
}
