#include "task_widget.h"
#include "time_dialog.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QCheckBox>

GroupTask::GroupTask( QTask qtask, int hidingCheck, TaskWidget* parent )
{
	this->qtask = qtask;
	this->parent = parent;
	this->isHidingTask = (hidingCheck==Qt::Checked)?true:false;

	finishTaskCheck = new QCheckBox;
	addWidget( finishTaskCheck );

	usingTime = new QLabel( QString::number(qtask.usingTime) );
	addWidget( usingTime );
	
	needingTime = new QLabel( QString::number(qtask.needingTime) );
	addWidget( needingTime );

	taskTag = new QLabel( qtask.tag );
	addWidget( taskTag );

	taskName = new QLabel( qtask.name );
	addWidget( taskName );

	chooseTaskCheck = new QCheckBox;
	addWidget( chooseTaskCheck );

	connect( finishTaskCheck, SIGNAL(stateChanged(int)),
			this, SLOT(finishTask(int)) );
	connect( chooseTaskCheck, SIGNAL(stateChanged(int)),
			this, SLOT(chooseTask(int)) );
	updateDisplay();
}

GroupTask::~GroupTask( void )
{
	delete taskName;
	delete finishTaskCheck;
	delete chooseTaskCheck;
}

int GroupTask::getID( void )
{
	return qtask.id;
}

void GroupTask::updateTask( QTask qtask )
{
	this->qtask = qtask;
	usingTime->setText( QString::number(qtask.usingTime) );
	
	//usingTime->show();
}

void GroupTask::finishTask( int state )
{
	parent->finishChildTask( qtask.id );
}

void GroupTask::chooseTask( int state )
{
	parent->chooseChildTask( qtask.id );
}

void GroupTask::setHidingState( bool isHidingTask )
{
	this->isHidingTask = isHidingTask;
	updateDisplay();
}

void GroupTask::updateDisplay( void )
{
	if( qtask.finished && isHidingTask ) {
		hide();
	}
	else {
		show();
	}
}

void GroupTask::hide( void )
{
	finishTaskCheck->hide();
	chooseTaskCheck->hide();
	usingTime->hide();
	needingTime->hide();
	taskTag->hide();
	taskName->hide();
}

void GroupTask::show( void )
{
	finishTaskCheck->show();
	chooseTaskCheck->show();
	usingTime->show();
	needingTime->show();
	taskTag->show();
	taskName->show();
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

	showFinish = new QCheckBox( tr("finish?") );
	//connect( showFinish, SIGNAL(tr

	midLayout = new QVBoxLayout;
	midLayout->addStretch( 0 );
	midLayout->addWidget( workingTime );
	midLayout->addWidget( restingTime );
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
	delete restingTime;
	delete workingTime;
	for( std::vector<GroupTask*>::iterator i = taskGroup.begin(); i != taskGroup.end(); ++i ) {
		//delete *i;
	}
	taskGroup.clear();
}

void TaskWidget::finishChildTask( int id )
{
	std::wcout << "hhhhhhhhhh" << std::endl;
	emit finishTask( id );
}

void TaskWidget::chooseChildTask( int id )
{
	emit chooseTask( id );
}

void TaskWidget::updateTask( QTask qtask )
{
	std::wcout << L"TaskWidget::updateTask" << std::endl;
	std::vector<GroupTask*>::iterator ptr = taskGroup.end();
	for( std::vector<GroupTask*>::iterator i=taskGroup.begin(); i != taskGroup.end(); ++i ) {
		//std::wcout << L"start" << std::endl;
		if( (*i)->getID() == qtask.id ) {
			ptr = i;
			break;
		}
		//std::wcout << L"end" << std::endl;
	}
	if( ptr == taskGroup.end() ) {
		//std::wcout << L"start" << std::endl;
		GroupTask* gTask = new GroupTask( qtask,showFinish->checkState(), this );
		taskGroup.push_back( gTask );
		leftLayout->addLayout( gTask );
	}
	else {
		(*ptr)->updateTask( qtask );
		(*ptr)->updateDisplay();
	}
	std::wcout << L"end" << std::endl;
}

void TaskWidget::doStart( void )
{
	emit start();
}

void TaskWidget::hideTask( int state )
{
	bool isHidingTask = state==Qt::Checked?false:true;
	for( int i=0; i<taskGroup.size(); ++i ) {
		taskGroup[i]->setHidingState( isHidingTask );
	}
}
