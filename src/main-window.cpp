#include "main-window.h"

#include <QTabWidget>
#include <QMenuBar>
//#include <iostream>

#include "qtomato.h"
#include "new-task-dialog.h"
#include "task-widget.h"
#include "data-time-widget.h"
#include "time-dialog.h"
#include "timer.h"
#include "task-status-widget.h"


namespace tomato {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	tomato_ = new QTomato;
	timer_ = new Timer;

	main_widget_ = new QTabWidget;
	setCentralWidget(main_widget_);

	task_widget_ = new TaskWidget;
	main_widget_->addTab(task_widget_, tr("main page"));

	new_task_dialog_ = new NewTaskDialog;
	data_time_widget_ = new DataTimeWidget;
  task_status_widget_ = new TaskStatusWidget;

	work_dialog_ = new TimeDialog;
	work_dialog_->setWindowTitle("working");
	work_dialog_->setModal(true);

	rest_dialog_ = new TimeDialog;
	rest_dialog_->setWindowTitle("resting");
	rest_dialog_->setModal(true);
	QFont font;
	font.setPointSize(30);
	rest_dialog_->setFont(font);

	CreateMenuBar();

	connect(task_widget_, SIGNAL(Start()),
			this, SLOT(Start()));

	ConnectUpdateData();
	ConnectDataStream();
	ConnectTimer();

	connect(task_widget_, SIGNAL(WorkTimeChanged(int)),
			this, SLOT(ChangeWorkTime(int)));
	connect(task_widget_, SIGNAL(RestTimeChanged(int)),
			this, SLOT(ChangeRestTime(int)));

	Load();
}

MainWindow::~MainWindow() {
	delete add_task_;
	delete file_menu_;
	delete new_task_dialog_;
	delete show_data_;
  delete show_task_status_;
	delete data_menu_;
	delete data_time_widget_;
  delete task_status_widget_;
	delete task_widget_;
	delete tomato_;

	delete work_dialog_;
	delete rest_dialog_;

	delete main_widget_;
}

void MainWindow::Load() {
	tomato_->Load();
	task_widget_->Load();
	new_task_dialog_->Load();
}

void MainWindow::CreateMenuBar() {
	file_menu_ = new QMenu(tr("file"));
	add_task_ = new QAction(tr("new task"), this);
	file_menu_->addAction(add_task_);
	menuBar()->addMenu(file_menu_);
	connect(add_task_, SIGNAL(triggered()),
			new_task_dialog_, SLOT(show()));
	data_menu_ = new QMenu(tr("data"));
	show_data_ = new QAction(tr("show data"), this);
  show_task_status_ = new QAction(tr("show task status"), this);
	data_menu_->addAction(show_data_);
  data_menu_->addAction(show_task_status_);
	menuBar()->addMenu(data_menu_);
	connect(show_data_, SIGNAL(triggered()),
			data_time_widget_, SLOT(show()));
  connect(show_task_status_, SIGNAL(triggered()),
      task_status_widget_, SLOT(show()));
}

void MainWindow::ConnectDataStream() {
	connect(tomato_, SIGNAL(UpdateTask(const std::vector<QTask>&)),
			task_widget_, SLOT(UpdateTask(const std::vector<QTask>&)));
	connect(tomato_, SIGNAL(UpdateDataTime(const std::vector<QDataTime>&)),
			data_time_widget_, SLOT(UpdateDataTime(const std::vector<QDataTime>&)));
	connect(tomato_, SIGNAL(UpdateTask(const std::vector<QTask>&)),
			task_status_widget_, SLOT(UpdateTask(const std::vector<QTask>&)));
}

void MainWindow::ConnectUpdateData() {
	connect(new_task_dialog_, SIGNAL(AddTask(QTask)),
			tomato_, SLOT(AddTask(QTask)));
	connect(task_widget_, SIGNAL(ChooseTask(int, bool)),
			tomato_, SLOT(ChooseTask(int, bool)));
	connect(task_widget_, SIGNAL(FinishTask(int, bool)),
			tomato_, SLOT(FinishTask(int, bool)));
	connect(tomato_, SIGNAL(UpdateTask(QTask)),
			task_widget_, SLOT(UpdateTask(QTask)));
}

void MainWindow::ConnectTimer() {
	connect(timer_, SIGNAL(FinishWork()),
			this, SLOT(FinishWork()));
	connect(timer_, SIGNAL(FinishRest()),
			this, SLOT(FinishRest()));
	connect(timer_, SIGNAL(DisplayTime(int)),
			work_dialog_, SLOT(ChangeTime(int)));
	connect(timer_, SIGNAL(DisplayTime(int)),
			rest_dialog_, SLOT(ChangeTime(int)));
}


void MainWindow::Start() {
	tomato_->Start(work_time_, rest_time_);
	timer_->Start();
	work_dialog_->show();
}

void MainWindow::FinishRest() {
	tomato_->End();
	rest_dialog_->hide();
}

void MainWindow::FinishWork() {
	work_dialog_->hide();
	rest_dialog_->showFullScreen();
}


void MainWindow::ChangeRestTime(int minutes) {
	rest_time_ = minutes;
	timer_->SetTimer(work_time_, rest_time_);
}

void MainWindow::ChangeWorkTime(int minutes) {
	work_time_ = minutes;
	timer_->SetTimer(work_time_, rest_time_);
}

}

