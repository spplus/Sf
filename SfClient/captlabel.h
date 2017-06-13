#ifndef __CAPTLABEL_H__
#define __CAPTLABEL_H__

#include <QtGui>

class CaptLabel		:public QLabel	
{
	Q_OBJECT
public:
	CaptLabel(QWidget* parent=NULL);
signals:
	void	pressed();
protected:
	void	mousePressEvent ( QMouseEvent * ev );
};

#endif