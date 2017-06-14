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
	void	setContext(int row,QString factory,QString user,QString pwd);

signals:
	void	loginResp(int row,Json::Value &jvalue);	
public slots:
	void	replyFinished(QNetworkReply *reply);

	void	loadImg();
	void	longin();

private:
	void		initUi();
	void		parseCaptResp(Json::Value &jvalue);
	void		pareLoginResp(Json::Value& jvalue);

private:

	int				m_rownum;
	QTimer			m_captTimer;
	QString			m_factory;
	QString			m_user;
	QString			m_pwd;
	QLineEdit*		m_capt;
	QString			m_sessionId;
	QString			m_timeStamp;
	CaptLabel*		m_captchaImg;
	QPushButton*	m_loginBtn;

	QNetworkAccessManager	m_netMgr;
};


#endif