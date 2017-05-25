#include <QCloseEvent>
#include "spwebview.h"

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
}