#include <QCloseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include "spwebview.h"

SpWebView::SpWebView()
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("思方来电助手");
	setMinimumWidth(800);
}

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
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