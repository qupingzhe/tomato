#include "task_box.h"

#include "task_widget.h"

#include <QLabel>
#include <QCheckBox>

TaskBox::TaskBox( QTask qtask, int hidingCheck, TaskWidget* parent )
{
	this->qtask = qtask;
	this->parent = parent;
	this->isHidingTask = (hidingCheck==Qt::Checked)?false:true;
	this->clearFlag = false;

	finishTaskCheck = new QCheckBox;
	if( qtask.finished ) {
		finishTaskCheck->setCheckState( Qt::Checked );
	}
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

TaskBox::~TaskBox( void )
{
	delete taskName;
	delete finishTaskCheck;
	delete chooseTaskCheck;
}

int TaskBox::getID( void )
{
	return qtask.id;
}

void TaskBox::updateTask( QTask qtask )
{
	this->qtask = qtask;
	usingTime->setText( QString::number(qtask.usingTime) );
	if( qtask.finished ) {
		finishTaskCheck->setCheckState( Qt::Checked );
	}
	else {
		finishTaskCheck->setCheckState( Qt::Unchecked );
	}
	clearFlag = true;
	if( qtask.choosed ) {
		chooseTaskCheck->setCheckState( Qt::Checked );
	}
	else {
		chooseTaskCheck->setCheckState( Qt::Unchecked );
	}
	clearFlag = false;
}

void TaskBox::finishTask( int state )
{
	parent->finishChildTask( qtask.id, state == Qt::Checked );
}

void TaskBox::chooseTask( int state )
{
	if( !clearFlag ) {
		parent->chooseChildTask( qtask.id, state == Qt::Checked );
	}
}

void TaskBox::setHidingState( bool isHidingTask )
{
	this->isHidingTask = isHidingTask;
	updateDisplay();
}

void TaskBox::updateDisplay( void )
{
	if( qtask.finished && isHidingTask ) {
		hide();
	}
	else {
		show();
	}
}

void TaskBox::hide( void )
{
	finishTaskCheck->hide();
	chooseTaskCheck->hide();
	usingTime->hide();
	needingTime->hide();
	taskTag->hide();
	taskName->hide();
}

void TaskBox::show( void )
{
	finishTaskCheck->show();
	chooseTaskCheck->show();
	usingTime->show();
	needingTime->show();
	taskTag->show();
	taskName->show();
}

