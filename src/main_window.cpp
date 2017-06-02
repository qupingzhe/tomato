#include "main_window.h"

#include "qtomato.h"
#include "new_task_dialog.h"
#include "task_widget.h"
#include "task_data_widget.h"
#include "time_dialog.h"
#include "timer.h"

#include <QTabWidget>
#include <QMenuBar>

#include <iostream>

TomatoMainWindow::TomatoMainWindow( QWidget* parent ) : QMainWindow( parent )
{
	tomato = new QTomato;
	timer = new TomatoTimer;

	mainWidget = new QTabWidget;
	taskWidget = new TaskWidget;

	newTaskDialog = new NewTaskDialog;
	taskDataWidget = new TaskDataWidget;

	workingDialog = new TimeDialog;
	workingDialog->setWindowTitle( "working" );
	restingDialog = new TimeDialog;
	restingDialog->setWindowTitle( "resting" );
	QFont font;
	font.setPointSize( 30 );
	restingDialog->setFont( font );

	createMenuBar();

	taskDataWidget->hide();

	mainWidget->addTab( taskWidget, tr("main page") );
	//mainWidget->addTab( taskDataWidget, tr("task data") );
	setCentralWidget( mainWidget );

	connect( taskWidget, SIGNAL(start()),
			this, SLOT(start()) );

	connectUpdateData();
	connectDataStream();
	connectTimer();

	connect( taskWidget, SIGNAL(workTimeChanged(int)),
			this, SLOT(changeWorkTime(int)) );
	connect( taskWidget, SIGNAL(restTimeChanged(int)),
			this, SLOT(changeRestTime(int)) );

	workingDialog->setModal( true );
	restingDialog->setModal( true );
	load();
}

void TomatoMainWindow::connectDataStream( void )
{
	connect( tomato, SIGNAL(updateTask(const std::vector<QTask>&)),
			taskWidget, SLOT(updateTask(const std::vector<QTask>&)) );
	connect( tomato, SIGNAL(updateTaskData(const std::vector<QTaskData>&)),
			taskDataWidget, SLOT(updateTaskData(const std::vector<QTaskData>)) );
}

void TomatoMainWindow::connectUpdateData( void )
{
	connect( newTaskDialog, SIGNAL(addTask(QTask)),
			tomato, SLOT(addTask(QTask)) );
	connect( taskWidget, SIGNAL(chooseTask(int)),
			tomato, SLOT(chooseTask(int)) );
	connect( taskWidget, SIGNAL(finishTask(int)),
			tomato, SLOT(finishTask(int)) );
	connect( tomato, SIGNAL(updateTask(QTask)),
			taskWidget, SLOT(updateTask(QTask)) );
}

void TomatoMainWIndow::connectTimer( void )
{
	connect( timer, SIGNAL(finishWork()),
			this, SLOT(finishWork()) );
	connect( timer, SIGNAL(finishRest()),
			this, SLOT(finishRest()) );
	connect( timer, SIGNAL(displayTime(int)),
			workingDialog, SLOT(changeTime(int)) );
	connect( timer, SIGNAL(displayTime(int)),
			restingDialog, SLOT(changeTime(int)) );
}

void TomatoMainWindow::load( void )
{
	tomato->load();
	taskWidget->load();
	timer->setTime( workTime, restTime );
	newTaskDialog->load();
	//taskDataWidget->load();
}

TomatoMainWindow::~TomatoMainWindow( void )
{
	delete addTask;
	delete fileMenu;
	delete newTaskDialog;
	delete showData;
	delete dataMenu;
	delete taskDataWidget;

	delete taskWidget;
	delete tomato;

	delete workingDialog;
	delete restingDialog;

	delete mainWidget;
}

void TomatoMainWindow::createMenuBar( void )
{
	fileMenu = new QMenu( tr("file") );
	addTask = new QAction( tr("new task"), this ) ;
	fileMenu->addAction( addTask );
	menuBar()->addMenu( fileMenu );
	connect( addTask, SIGNAL(triggered()),
			newTaskDialog, SLOT(show()) );
	dataMenu = new QMenu( tr("data") );
	showData = new QAction( tr("show data"), this );
	dataMenu->addAction(showData);
	menuBar()->addMenu(dataMenu);
	connect( showData, SIGNAL(triggered()),
			taskDataWidget, SLOT(show()) );
}

void TomatoMainWindow::finishRest( void )
{
	tomato->end();
	restingDialog->hide();
}

void TomatoMainWindow::finishWork( void )
{
	workingDialog->hide();
	restingDialog->showFullScreen();
}

void TomatoMainWindow::start( void )
{
	tomato->start( workTime, restTime );
	timer->start();
	workingDialog->show();
}

void TomatoMainWindow::changeRestTime( int minutes )
{
	this->restTime = minutes;
	timer->setTime( workTime, restTime );
}

void TomatoMainWindow::changeWorkTime( int minutes )
{
	this->workTime = minutes;
	timer->setTime( workTime, restTime );
}

