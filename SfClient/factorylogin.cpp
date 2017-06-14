#include <QNetworkRequest>
#include <QNetworkReply>
#include "factorylogin.h"
#include "configer.h"
#include <string>
#include "common.h"
using namespace std;

FactoryLogin::FactoryLogin(QWidget* parent):QDialog(parent)
{
	m_rownum = 0;
	m_factory = FACTORY_MEDIA;

	initUi();
	m_captTimer.setInterval(SF_CAPTCHA_INTERVAL);

	setWindowTitle("请输入验证码");
	connect(&m_netMgr, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
	connect(m_captchaImg,SIGNAL(pressed()),this,SLOT(loadImg()));
	connect(m_loginBtn,SIGNAL(pressed()),this,SLOT(longin()));
	connect(&m_captTimer,SIGNAL(timeout()),this,SLOT(loadImg()));
	loadImg();
	setFixedSize(220,140);
	setWindowFlags(Qt::WindowMaximizeButtonHint|Qt::Dialog);
	
}

void FactoryLogin::initUi()
{
	QVBoxLayout*	mbox = new QVBoxLayout;
	QVBoxLayout*	vbox = new QVBoxLayout;
	QHBoxLayout*	hbox = new QHBoxLayout;
	QHBoxLayout*	h2box = new QHBoxLayout;
	m_capt = new QLineEdit;

	m_loginBtn = new QPushButton("登陆");
	m_capt->setMinimumHeight(35);
	m_capt->setPlaceholderText("请输入验证码");

	m_captchaImg = new CaptLabel;
	hbox->addStretch();
	hbox->addWidget(m_captchaImg);
	hbox->addStretch();
	vbox->addLayout(hbox);
	vbox->addWidget(m_capt);
	h2box->addStretch();
	h2box->addWidget(m_loginBtn);
	h2box->addStretch();
	mbox->addLayout(vbox);
	mbox->addLayout(h2box);
	setLayout(mbox);
}

void FactoryLogin::showDlg()
{
	loadImg();
	show();
	m_captTimer.start();
}

void FactoryLogin::longin()
{
	QString xcode = m_capt->text();
	if (xcode.isEmpty())
	{
		QMessageBox::warning(this,"系统提示","请输入验证码");
		return;
	}
	QString json = QString("{\"user\":\"%1\",\"pwd\":\"%2\",\"factory\":\"%3\",\"xcode\":\"%4\",\"t\":\"%5\",\"sid\":\"%6\",\"mainServerHost\":\"%7\",\"statusReportHost\":\"%8\"}")
		.arg(m_user)
		.arg(m_pwd)
		.arg(m_factory)
		.arg(xcode)
		.arg(m_timeStamp)
		.arg(m_sessionId)
		.arg(URL_MAIN_SERVER)
		.arg(URL_REPT);
	QByteArray req ;
	req.append(json);

	QNetworkRequest request;
	request.setUrl(QUrl(URL_FACTORY_LONGIN));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json; charset=UTF-8");
	m_netMgr.post(request,req);

	this->accept();
	m_captTimer.stop();
}

void FactoryLogin::loadImg()
{
	QNetworkRequest request;
	request.setUrl(QUrl(URL_CAPTCHA));
	m_netMgr.get(request);
	m_capt->setText("");
}

void FactoryLogin::replyFinished(QNetworkReply *reply)
{
	QString msg = QString::fromUtf8(reply->readAll());
	qDebug("%s",msg);
	Json::Reader reader;
	Json::Value value;
	
	if(reader.parse(msg.toStdString(),value))
	{
		string capt = value["captcha"].asString();
		if (capt.length()>0)
		{
			parseCaptResp(value);
		}
		else 
		{
			pareLoginResp(value);
		}
		

	}
}

void FactoryLogin::parseCaptResp(Json::Value &jvalue)
{
	string capt = jvalue["captcha"].asString();
	m_sessionId = jvalue["sid"].asString().c_str();
	m_timeStamp = jvalue["t"].asString().c_str();
	QByteArray pixdata = QByteArray::fromBase64(capt.c_str());
	QPixmap pixmap;
	pixmap.loadFromData(pixdata);
	m_captchaImg->setPixmap(pixmap);
}

void FactoryLogin::pareLoginResp(Json::Value& jvalue)
{
	emit loginResp(m_rownum,jvalue);
}


void FactoryLogin::setContext(int row,QString factory,QString user,QString pwd)
{
	m_rownum = row;
	m_factory = factory;
	m_user = user;
	m_pwd = pwd;
}