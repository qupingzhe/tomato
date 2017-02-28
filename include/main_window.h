#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

class TomatoClock;
class TaskDialog;

class QTabWidget;
class QMenu;
class QAction;
class QTimer;

class TomatoMainWindow : public QMainWindow
{
	Q_OBJECT
public:
	TomatoMainWindow( QWidget* parent = NULL );
	~TomatoMainWindow( void );
private slots:
	void doStart( void );
private:
	QTabWidget* mainWidget;
	TomatoClock* tomatoClock;
	TaskDialog* taskDialog;

	QMenu* fileMenu;
	QAction* addTask;
	QTimer* timer;
};

#endif
