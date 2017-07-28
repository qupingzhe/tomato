#include "new-task-dialog.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QTextStream>
#include <QComboBox>
#include <QFile>

#include "configuration.h"

namespace tomato {

NewTaskDialog::NewTaskDialog(QWidget* parent) : QDialog(parent) {
	main_layout_= new QFormLayout;

	tag_label_ = new QLabel(tr("tag"));
	tag_ = new QComboBox;
	main_layout_->addRow(tag_label_, tag_);

	task_name_label_ = new QLabel(tr("task name"));
	task_name_ = new QLineEdit;
	main_layout_->addRow(task_name_label_, task_name_);

	needing_time_label_ = new QLabel(tr("needing time"));
	needing_time_ = new QSpinBox;
	main_layout_->addRow(needing_time_label_, needing_time_);

	add_button_ = new QPushButton(tr("Add"));
	cancel_button_ = new QPushButton(tr("Cancel"));
	main_layout_->addRow(add_button_, cancel_button_);

	setLayout(main_layout_);

	connect(add_button_, SIGNAL(clicked()),
			this, SLOT(Add()));
	connect(cancel_button_, SIGNAL(clicked()),
			this, SLOT(hide()));
}

NewTaskDialog::~NewTaskDialog() {
	delete main_layout_;
	delete add_button_;
	delete cancel_button_;

	delete tag_label_;
	delete tag_;

	delete task_name_label_;
	delete task_name_;

	delete needing_time_label_;
	delete needing_time_;
}

void NewTaskDialog::Load() {
  for (std::vector<QConfigurationData>::const_iterator i = g_configuration.BeginForConfigurationData();
      i != g_configuration.EndForConfigurationData(); ++i) {
    tag_->addItem(i->tag);
  }

  /*
	QFile file( "./etc/tomato.conf" );
	if (!file.open(QIODevice::ReadOnly)) {
		return ;
	}
	QTextStream in( &file );
	QString tmp;
	while (!in.atEnd()) {
		tag_->addItem(in.readLine());
	}
	file.close();
  */
}

void NewTaskDialog::Add() {
	QTask qtask;
	qtask.tag = tag_->currentText();
	qtask.name = task_name_->displayText();
	qtask.basic_task.needing_time = needing_time_->value();
	emit AddTask(qtask);
	hide();
}

}

