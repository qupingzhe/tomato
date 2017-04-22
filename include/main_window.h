#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QTomato;
class TaskWidget;
class TaskDataWidget;
class NewTaskDialog;
class TimeDialog;
class TomatoTimer;

class QTabWidget;
class QMenu;
class QAction;

class TomatoMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	TomatoMainWindow( QWidget* parent = NULL );
	void load( void );
	void createMenuBar( void );
	~TomatoMainWindow( void );
private slots:
	void start( void );
	void finishRest( void );
	void finishWork( void );
	void changeWorkTime( int minutes );
	void changeRestTime( int minutes );
private:
	QTomato* tomato;
	QTabWidget* mainWidget;
	TaskWidget* taskWidget;
	TaskDataWidget* taskDataWidget;
	TimeDialog* workingDialog;
	TimeDialog* restingDialog;

	NewTaskDialog* newTaskDialog;

	QMenu* fileMenu;
	QAction* addTask;
	TomatoTimer* timer;
	int restTime;
	int workTime;
};

#endif
