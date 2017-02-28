#ifndef TOMATO_CLOCK_H
#define TOMATO_CLOCK_H

#include <QWidget>

class QPushButton;
class QLayout;
class TimeLabel;
class QDialog;

class TomatoClock : public QWidget
{
	Q_OBJECT
public:
	TomatoClock( QWidget* parent = NULL );
	~TomatoClock( void );
signals:
	void start( void );
private slots:
	void doStart( void );
	void rest( void );
	void work( void );
private:
	QPushButton* startButton;
	QLayout* mainLayout;
	TimeLabel* timeLabel;
	QDialog* dialog;
	TimeLabel* timeInDialog;
};

#endif
