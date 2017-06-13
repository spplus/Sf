#ifndef __FACTORYLOGIN_H__
#define __FACTORYLOGIN_H__

#include <QNetworkAccessManager>
#include <QtGui>
#include "captlabel.h"
#include "jsoncpp/json.h"
class FactoryLogin	:public QDialog
{
	Q_OBJECT
public:
	FactoryLogin(QWidget* parent);
	void	showDlg();
public slots:
	void	replyFinished(QNetworkReply *reply);

	void	loadImg();
	void	longin();

private:
	void		parseCaptResp(Json::Value &jvalue);
	void		pareLoginResp(Json::Value& jvalue);

private:
	QLineEdit*		m_capt;
	QString			m_sessionId;
	QString			m_timeStamp;
	CaptLabel*		m_captchaImg;
	QPushButton*	m_loginBtn;

	QNetworkAccessManager	m_netMgr;
};


#endif