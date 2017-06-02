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
	~TomatoMainWindow( void );
	void load( void );
	void createMenuBar( void );
	void connectDataStream( void );
	void connectUpdateData( void );
	void connectTimer( void );
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
	QMenu* dataMenu;
	QAction* showData;

	TomatoTimer* timer;
	int restTime;
	int workTime;
};

#endif
