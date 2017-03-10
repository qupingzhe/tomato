#include "new_task_dialog.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>

NewTaskDialog::NewTaskDialog( QWidget* parent ) : QDialog( parent )
{
	mainLayout = new QFormLayout;

	classificationLabel = new QLabel( tr("classification") );
	classification = new QLineEdit;
	mainLayout->addRow( classificationLabel, classification);

	tagLabel = new QLabel( tr("tag") );
	tag = new QLineEdit;
	mainLayout->addRow( tagLabel, tag );

	taskNameLabel = new QLabel( tr("task name") );
	taskName = new QLineEdit;
	mainLayout->addRow( taskNameLabel, taskName );

	needingTimeLabel = new QLabel( tr("needing time") );
	needingTime = new QSpinBox;
	mainLayout->addRow( needingTimeLabel, needingTime );

	addButton = new QPushButton( tr("Add") );
	cancelButton = new QPushButton( tr("Cancel") );
	mainLayout->addRow( addButton, cancelButton );

	setLayout( mainLayout );

	connect( addButton, SIGNAL(clicked()),
			this, SLOT(add()) );
	connect( cancelButton, SIGNAL(clicked()),
			this, SLOT(cancel()) );
}

NewTaskDialog::~NewTaskDialog( void )
{
	delete classificationLabel;
	delete classification;
	delete tagLabel;
	delete tag;
	delete taskNameLabel;
	delete taskName;
	delete needingTimeLabel;
	delete needingTime;
	delete addButton;
	delete cancelButton;
}

void NewTaskDialog::add( void )
{
	QTask qtask;
	qtask.classification = classification->displayText();
	qtask.tag = tag->displayText();
	qtask.name = taskName->displayText();
	qtask.needingTime = needingTime->value();
	emit addTask( qtask );
	cancel();
}

void NewTaskDialog::cancel( void )
{
	this->hide();
}
