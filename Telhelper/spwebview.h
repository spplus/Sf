#ifndef __SPWEBVIEW_H__
#define __SPWEBVIEW_H__

#include <QWebView>

class SpWebView :public QWebView
{
public:
	SpWebView();
	void		closeEvent(QCloseEvent *event);
	void		showWindow();
};

#endif
