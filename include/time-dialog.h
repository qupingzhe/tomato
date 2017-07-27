#ifndef TIME_DIALOG_H
#define TIME_DIALOG_H

#include <QDialog>
#include <QString>

class QLabel;
class QHBoxLayout;

namespace tomato {
class TimeDialog : public QDialog {
	Q_OBJECT
public:
	TimeDialog();
	~TimeDialog();
	static QString ToString(int time) {
		int s_min = time / 60;
		int s_sec1 = (time % 60) / 10;
		int s_sec2 = (time % 60) % 10;
		return QString("%1:%2%3").arg(s_min)
				                     .arg(s_sec1)
                      			 .arg(s_sec2);
	}
public slots:
	void ChangeTime(int time);
private:
	QLabel* label_;
	QHBoxLayout* layout_;
};

}

#endif
