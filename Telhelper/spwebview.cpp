#include <QCloseEvent>
#include "spwebview.h"

SpWebView::SpWebView()
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("思方来电助手");
}

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
}