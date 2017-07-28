#ifndef TOMATO_MAIN_WINDOW_H
#define TOMATO_MAIN_WINDOW_H

#include <QMainWindow>

class QTabWidget;
class QMenu;
class QAction;

namespace tomato {

class QTomato;
class TaskWidget;
class DataTimeWidget;
class NewTaskDialog;
class TimeDialog;
class Timer;

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	MainWindow(QWidget* parent = NULL);
	~MainWindow();
	void Load();
	void CreateMenuBar();
	void ConnectDataStream();
	void ConnectUpdateData();
	void ConnectTimer();
private slots:
	void Start();
	void FinishRest();
	void FinishWork();
	void ChangeWorkTime(int minutes);
	void ChangeRestTime(int minutes);
private:
	QTomato* tomato_;
	QTabWidget* main_widget_;
	TaskWidget* task_widget_;
	DataTimeWidget* data_time_widget_;
	TimeDialog* work_dialog_;
	TimeDialog* rest_dialog_;

	NewTaskDialog* new_task_dialog_;

	QMenu* file_menu_;
	QAction* add_task_;
	QMenu* data_menu_;
	QAction* show_data_;

	Timer* timer_;
	int rest_time_;
	int work_time_;
};

}

#endif
