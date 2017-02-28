#include "main_window.h"

#include "tomato_clock.h"
#include "task_dialog.h"

#include <QTabWidget>
#include <QMenuBar>
#include <QTimer>

#include <ctime>
#include <cstdio>
#include <iostream>

TomatoMainWindow::TomatoMainWindow( QWidget* parent ) : QMainWindow( parent )
{
	mainWidget = new QTabWidget;
	tomatoClock = new TomatoClock(this);
	mainWidget->addTab( tomatoClock, tr("main page") );
	setCentralWidget( mainWidget );

	fileMenu = new QMenu( tr("file") );
	addTask = new QAction( tr("new task"), this ) ;
	fileMenu->addAction( addTask );
	menuBar()->addMenu( fileMenu );

	connect( tomatoClock, SIGNAL(start()),
			this, SLOT(doStart()) );

	taskDialog = new TaskDialog;

	connect( addTask, SIGNAL(triggered()),
			taskDialog, SLOT(show()) );
}

TomatoMainWindow::~TomatoMainWindow( void )
{
	delete addTask;
	delete fileMenu;
	delete tomatoClock;
	delete mainWidget;
	delete timer;
	delete taskDialog;
}

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
