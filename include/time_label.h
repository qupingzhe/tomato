#ifndef TIME_LABEL_H
#define TIME_LABEL_H

#include <QLabel>
#include <QString>

class QTimer;

class TimeLabel : public QLabel
{
	Q_OBJECT
public:
	TimeLabel( int min, QWidget* parent = NULL );
	~TimeLabel( void );
	QString getTime( void );
signals:
	void timeout( void );
public slots:
	void restart( void );
private slots:
	void updateTime( void );
	
private:
	QTimer* timer;
	int seconds;
	int mins;
};

#endif
