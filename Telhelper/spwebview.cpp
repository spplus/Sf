#include <QCloseEvent>
#include "spwebview.h"

SpWebView::SpWebView()
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("˼����������");
}

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//���ش���  
	event->ignore();//���Թر��¼�  
}