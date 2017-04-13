#include "main_window.h"

#include "qtomato.h"
#include "new_task_dialog.h"
#include "task_widget.h"
#include "time_dialog.h"
#include "timer.h"

#include <QTabWidget>
#include <QMenuBar>

//#include <ctime>
//#include <cstdio>
#include <iostream>

TomatoMainWindow::TomatoMainWindow( QWidget* parent ) : QMainWindow( parent )
{
	tomato = new QTomato;
	timer = new TomatoTimer;
	//tomato->setTime( 3, 3 );
	mainWidget = new QTabWidget;
	taskWidget = new TaskWidget;

	newTaskDialog = new NewTaskDialog;

	workingDialog = new TimeDialog;
	workingDialog->setWindowTitle( "working" );
	restingDialog = new TimeDialog;
	restingDialog->setWindowTitle( "resting" );
	QFont font;
	font.setPointSize( 30 );
	restingDialog->setFont( font );

	createMenuBar();

	mainWidget->addTab( taskWidget, tr("main page") );
	setCentralWidget( mainWidget );

	connect( newTaskDialog, SIGNAL(addTask(QTask)),
			tomato, SLOT(addTask(QTask)) );
	connect( taskWidget, SIGNAL(chooseTask(int)),
			tomato, SLOT(chooseTask(int)) );
	connect( taskWidget, SIGNAL(finishTask(int)),
			tomato, SLOT(finishTask(int)) );

	connect( tomato, SIGNAL(updateTask(QTask)),
			taskWidget, SLOT(updateTask(QTask)) );
	connect( tomato, SIGNAL(updateTask(std::vector<QTask>&)),
			taskWidget, SLOT(updateTask(std::vector<QTask>&)) );

	connect( taskWidget, SIGNAL(start()),
			this, SLOT(start()) );

	connect( timer, SIGNAL(finishWork()),
			this, SLOT(finishWork()) );
	connect( timer, SIGNAL(finishRest()),
			this, SLOT(finishRest()) );
	connect( timer, SIGNAL(displayTime(int)),
			workingDialog, SLOT(changeTime(int)) );
	connect( timer, SIGNAL(displayTime(int)),
			restingDialog, SLOT(changeTime(int)) );
	load();
}

void TomatoMainWindow::load( void )
{
	tomato->load();
	timer->setTime( 25, 5 );
}

TomatoMainWindow::~TomatoMainWindow( void )
{
	delete addTask;
	delete fileMenu;
	delete newTaskDialog;

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
}

void TomatoMainWindow::finishRest( void )
{
	tomato->end();
	restingDialog->hide();
}

void TomatoMainWindow::finishWork( void )
{
	restingDialog->showFullScreen();
	workingDialog->hide();
	restingDialog->show();

	//restingDialog->exec();
}

void TomatoMainWindow::start( void )
{
	tomato->start( 25, 5 );
	timer->start();
	workingDialog->show();
}
