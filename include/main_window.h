#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class QTomato;
class TaskWidget;
class NewTaskDialog;
class TimeDialog;

class QTabWidget;
class QMenu;
class QAction;

class TomatoMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	TomatoMainWindow( QWidget* parent = NULL );
	void createMenuBar( void );
	~TomatoMainWindow( void );
private slots:
	void doStart( void );
	void finishRest( void );
	void finishWork( void );
private:
	QTomato* tomato;
	QTabWidget* mainWidget;
	TaskWidget* taskWidget;
	TimeDialog* workingDialog;
	TimeDialog* restingDialog;

	NewTaskDialog* newTaskDialog;

	QMenu* fileMenu;
	QAction* addTask;
};

#endif
