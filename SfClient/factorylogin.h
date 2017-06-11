#ifndef __FACTORYLOGIN_H__
#define __FACTORYLOGIN_H__

#include <QNetworkAccessManager>
#include <QtGui>

class FactoryLogin	:public QDialog
{
	Q_OBJECT
public:
	FactoryLogin(QWidget* parent);
	void	showDlg();
public slots:
	void replyFinished(QNetworkReply *reply);
private:
	void	loadImg();
private:
	QLabel*		m_captchaImg;
	QNetworkAccessManager	m_networkManager;
};


#endif