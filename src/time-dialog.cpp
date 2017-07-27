#include "time-dialog.h"

#include <QLabel>
#include <QHBoxLayout>

namespace tomato {
TimeDialog::TimeDialog() {
	layout_ = new QHBoxLayout;
	label_ = new QLabel();
	layout_->addWidget(label_);
	setLayout(layout_);
}

TimeDialog::~TimeDialog() {
	delete layout_;
	delete label_;
}

void TimeDialog::ChangeTime(int time) {
	label_->setText(ToString(time));
	label_->show();
}

}
