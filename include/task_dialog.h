#ifndef TASK_DIALOG_H
#define TASK_DIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QSpinBox;
class QFormLayout;

class TaskDialog : public QDialog
{
	Q_OBJECT
public:
	TaskDialog( QWidget* parent = NULL );
	~TaskDialog( void );
private:
	QLabel* classificationLabel;
	QLineEdit* classification;
	QLabel* tagLabel;
	QLineEdit* tag;
	QLabel* taskNameLabel;
	QLineEdit* taskName;
	QLabel* needingTimeLabel;
	QSpinBox* needingTime;

	QFormLayout* mainLayout;
};

#endif
