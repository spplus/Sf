#ifndef __FACTORYLOGIN_H__
#define __FACTORYLOGIN_H__

#include <QNetworkAccessManager>
#include <QtGui>
#include <string>
#include "captlabel.h"
#include "jsoncpp/json.h"

using namespace std;

class FactoryLogin	:public QDialog
{
	Q_OBJECT
public:
	FactoryLogin(QWidget* parent);
	int		showDlg();
	void	setContext(int row,QString factory,QString user,QString pwd);
	void	keyPressEvent ( QKeyEvent * event ) ;
signals:
	void	loginResp(Json::Value &jvalue);	
	void	loging(string, string);
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