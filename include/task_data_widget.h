#ifndef TASK_DATA_WIDGET_H
#define TASK_DATA_WIDGET_H

#include <QWidget>
#include <vector>

#include "qtask.h"
#include "task_data_box.h"


class TaskDataBox;
class QVBoxLayout;

class TaskDataWidget : public QWidget
{
	Q_OBJECT
public:
	TaskDataWidget( QWidget* parent = NULL );
	~TaskDataWidget( void );
	void load( void );
	static QColor getColor( QString tag )
	{
		static const QString book = QString::fromStdWString( L"看书" );
		static const QString blog = QString::fromStdWString( L"博客" );
		static const QString project = QString::fromStdWString( L"项目" );
		static const QString algorithm = QString::fromStdWString( L"算法" );
		static const QString homework = QString::fromStdWString( L"作业" );
		static const QString school = QString::fromStdWString( L"课堂" );
		Qt::GlobalColor value;
		if( tag ==  book ) {
			value = Qt::blue;
		} else if( tag ==  blog) {
			value = Qt::green;
		} else if( tag ==  project ) {
			value = Qt::red;
		} else if( tag == algorithm ) {
			value = Qt::yellow;
		} else if( tag ==  homework) {
			value = Qt::white;
		} else if( tag == school ) {
			value = Qt::cyan;
		} else {
			value = Qt::black;
		}
		return QColor(value);
	}
signals:
	void getTaskData( std::vector<QTaskData>& qtaskDatas );
protected:
	//void paintEvent( QPaintEvent* event );
private:
	std::vector<QTaskData> qtaskDatas;

	QVBoxLayout* layout;
	TaskDataBox** taskDataBox;
};

#endif
