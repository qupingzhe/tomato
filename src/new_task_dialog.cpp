#include "new_task_dialog.h"

#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>
#include <QTextStream>
#include <QComboBox>
#include <QFile>

//#include <iostream>

NewTaskDialog::NewTaskDialog( QWidget* parent ) : QDialog( parent )
{
	mainLayout = new QFormLayout;

	tagLabel = new QLabel( tr("tag") );
	tag = new QComboBox;
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
			this, SLOT(hide()) );
}

NewTaskDialog::~NewTaskDialog( void )
{
	delete mainLayout;
	delete addButton;
	delete cancelButton;

	delete tagLabel;
	delete tag;

	delete taskNameLabel;
	delete taskName;

	delete needingTimeLabel;
	delete needingTime;
}

void NewTaskDialog::load( void )
{
	QFile file( "./etc/tomato.conf" );
	if( !file.open( QIODevice::ReadOnly ) ) {
		return ;
	}
	QTextStream in( &file );
	QString tmp;
	while( !in.atEnd() ) {
		tag->addItem( in.readLine() );
	}
	file.close();
}

void NewTaskDialog::add( void )
{
	QTask qtask;
	qtask.tag = tag->currentText();
	qtask.name = taskName->displayText();
	qtask.needingTime = needingTime->value();
	emit addTask( qtask );
	hide();
}

