#include "captlabel.h"

CaptLabel::CaptLabel(QWidget* parent/* =NULL */):QLabel(parent)
{

}

void CaptLabel::mousePressEvent( QMouseEvent * ev )
{
	if (ev->button() == Qt::LeftButton)
	{
		emit pressed();
	}
	QLabel::mousePressEvent(ev);
}