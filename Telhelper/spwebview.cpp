#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include "spwebview.h"

SpWebView::SpWebView()
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("˼����������");
	setMinimumWidth(800);
}

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//���ش���  
	event->ignore();//���Թر��¼�  
}

void SpWebView::showWindow()
{

	int w = this->width();
	int h = this->height();
	int x = (QApplication::desktop()->width() - w)/2;
	int y = (QApplication::desktop()->height() - h)/2;
	this->show();
	this->activateWindow();
	setGeometry(QRect(x,y,w,h));
	
}