#include <QCloseEvent>
#include "spwebview.h"

void SpWebView::closeEvent(QCloseEvent *event)
{
	hide();//���ش���  
	event->ignore();//���Թر��¼�  
}