#include "timer.h"

#include <QTimer>

namespace tomato {

TomatoTimer::TomatoTimer() {
	timer_ = new QTimer;
	connect(timer_, SIGNAL(timeout()),
			this, SLOT(Timeout()));
}

TomatoTimer::~TomatoTimer() {
	timer_->stop();
	delete timer_;
}

void TomatoTimer::Start() {
	remaining_time_ = work_time_ + rest_time_;
	if (remaining_time_ > 0) {
		emit DisplayTime(remaining_time_ - rest_time_);
		timer_->start(1000);
	}
}

void TomatoTimer::SetTimer(int work_time, int rest_time) {
	work_time_ = work_time * 60;
	rest_time_ = rest_time * 60;
	//work_time_ = work_time;
	//rest_time_ = rest_time;
	remaining_time_ = work_time_ + rest_time_;
	emit DisplayTime(work_time_);
}

void TomatoTimer::Timeout() {
	--remaining_time_;
	if( remaining_time_ == rest_time_ ) {
		emit FinishWork();
	}
	if( remaining_time_ == 0 ) {
		emit FinishRest();
		timer_->stop();
		return ;
	}
	int tmp = remaining_time_ > rest_time_?
                remaining_time_ - rest_time_ : remaining_time_;
	emit DisplayTime(tmp);
	timer_->start(1000);
}

}
