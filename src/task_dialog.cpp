#include "task_dialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QFormLayout>

TaskDialog::TaskDialog( QWidget* parent ) : QDialog( parent )
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

	setLayout( mainLayout );
}

TaskDialog::~TaskDialog( void )
{
	delete classificationLabel;
	delete classification;
	delete tagLabel;
	delete tag;
	delete taskNameLabel;
	delete taskName;
	delete needingTimeLabel;
	delete needingTime;
}
