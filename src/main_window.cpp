#include "main_window.h"

#include "qtomato.h"
#include "new_task_dialog.h"
#include "task_widget.h"
#include "time_dialog.h"

#include <QTabWidget>
#include <QMenuBar>

//#include <ctime>
//#include <cstdio>

TomatoMainWindow::TomatoMainWindow( QWidget* parent ) : QMainWindow( parent )
{
	tomato = new QTomato;
	tomato->setTime( 3, 3 );
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
	connect( taskWidget, SIGNAL(start()),
			this, SLOT(doStart()) );

	connect( tomato, SIGNAL(getTask(QTask)),
			taskWidget, SLOT(getTask(QTask)) );
	connect( tomato, SIGNAL(finishWork()),
			this, SLOT(finishWork()) );
	connect( tomato, SIGNAL(finishRest()),
			this, SLOT(finishRest()) );
	connect( tomato, SIGNAL(changeTime(int)),
			workingDialog, SLOT(changeTime(int)) );
	connect( tomato, SIGNAL(changeTime(int)),
			restingDialog, SLOT(changeTime(int)) );
}

TomatoMainWindow::~TomatoMainWindow( void )
{
	delete addTask;
	delete fileMenu;
	delete taskWidget;
	delete workingDialog;
	delete restingDialog;
	delete mainWidget;
	delete newTaskDialog;
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

/*
void TomatoMainWindow::doStart( void )
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	tm nowTime;
	localtime_r(&time.tv_sec, &nowTime);
	FILE* file = fopen("./date/date","a");
	fprintf(file, "%04d %02d %02d ", nowTime.tm_year + 1900, nowTime.tm_mon, nowTime.tm_mday );
	fprintf(file,"%02d:%02d:%02d\n", nowTime.tm_hour, nowTime.tm_min, nowTime.tm_sec);
	fclose(file);
}
*/

void TomatoMainWindow::finishRest( void )
{
	restingDialog->hide();
}

void TomatoMainWindow::finishWork( void )
{
	restingDialog->showFullScreen();
	workingDialog->hide();
	restingDialog->show();

	//restingDialog->exec();
}

void TomatoMainWindow::doStart( void )
{
	tomato->start();
	workingDialog->show();
}
