#ifndef NEW_TASK_DIALOG_H
#define NEW_TASK_DIALOG_H

#include <QDialog>
#include "qtask.h"

class QLabel;
class QLineEdit;
class QSpinBox;
class QFormLayout;
class QPushButton;

class NewTaskDialog : public QDialog
{
	Q_OBJECT
public:
	NewTaskDialog( QWidget* parent = NULL );
	~NewTaskDialog( void );
signals:
	void addTask( QTask qtask );
private slots:
	void add( void );
	void cancel( void );
private:
	QLabel* tagLabel;
	QLineEdit* tag;

	QLabel* taskNameLabel;
	QLineEdit* taskName;

	QLabel* needingTimeLabel;
	QSpinBox* needingTime;

	QFormLayout* mainLayout;
	QPushButton* addButton;
	QPushButton* cancelButton;
};

#endif
