#ifndef NEW_TASK_DIALOG_H
#define NEW_TASK_DIALOG_H

#include <QDialog>
#include "qtask.h"

class QLabel;
class QLineEdit;
class QSpinBox;
class QFormLayout;
class QPushButton;
class QComboBox;

namespace tomato {

class NewTaskDialog : public QDialog {
	Q_OBJECT
public:
	NewTaskDialog(QWidget* parent = NULL);
	~NewTaskDialog();
	void Load();
signals:
	void AddTask(QTask qtask);
private slots:
	void Add();
private:
	QLabel* tag_label_;
	QComboBox* tag_;

	QLabel* task_name_label_;
	QLineEdit* task_name_;

	QLabel* needing_time_label_;
	QSpinBox* needing_time_;

	QFormLayout* main_layout_;
	QPushButton* add_button_;
	QPushButton* cancel_button_;
};

}

#endif
