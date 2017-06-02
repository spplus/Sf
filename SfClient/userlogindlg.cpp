#include <string>

#include "userlogindlg.h"
#include "qhttp/qhttpnetwork.h"
#include "jsoncpp/json.h"
#include "configer.h"
#include "topwidget.h"
#include "netclient.h"

using namespace std;

UserLogindlg::UserLogindlg()
	: QDialog()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->resize(600,440);
	setAutoFillBackground(true);

	//初始化为未按下鼠标左键
	mouse_press = false;

	iniUi();
	m_loginOk = false;
	m_md5pwd = "";

	connect(QhttpNetwork::instance(),SIGNAL(response(QByteArray)),this,SLOT(loginResp(QByteArray)));

}

UserLogindlg::~UserLogindlg()
{

}

bool UserLogindlg::isLogin()
{
	return m_loginOk;
}
void UserLogindlg::iniUi()
{
	QVBoxLayout* mbox = new QVBoxLayout;
	TopWidget* top = new TopWidget;
	

	QHBoxLayout* closeBtnBox = new QHBoxLayout;
	
	closeBtnBox->addWidget(top);


	int minH = 40;
	int mimW = 240;
	QHBoxLayout* userBox = new QHBoxLayout;
	QLabel* userIcon = new QLabel;

	m_userAccount = new QLineEdit;
	m_userAccount->setMinimumHeight(minH);
	m_userAccount->setMinimumWidth(mimW);
	m_userAccount->setPlaceholderText("请输入您的思方账号");
	//m_userAccount->setText("penghui1314");	// 调试账号
	userBox->addStretch();
	userBox->addWidget(userIcon);
	userBox->addWidget(m_userAccount);
	userBox->addStretch();

	QHBoxLayout* pwdBox = new QHBoxLayout;
	QLabel* pwdIcon = new QLabel;
	m_userPassword = new QLineEdit;
	m_userPassword->setMinimumHeight(minH);
	m_userPassword->setMinimumWidth(mimW);
	m_userPassword->setPlaceholderText("请输入您的密码");
	//m_userPassword->setText("15655154198");		// 调试账号密码
	m_userPassword->setEchoMode(QLineEdit::Password);

	pwdBox->addStretch();
	pwdBox->addWidget(pwdIcon);
	pwdBox->addWidget(m_userPassword);
	pwdBox->addStretch();

	QHBoxLayout* loginBox = new QHBoxLayout;
	m_loginBtn = new QPushButton("登录");
	m_loginBtn->setFixedSize(375,50);

	m_loginBtn->setObjectName("login");

	loginBox->addStretch();
	loginBox->addWidget(m_loginBtn);
	loginBox->addStretch();

	mbox->addLayout(closeBtnBox);
	mbox->addStretch(1);
	mbox->addLayout(userBox);
	mbox->addLayout(pwdBox);
	mbox->addStretch(1);
	mbox->addLayout(loginBox);
	mbox->addStretch(2);

	connect(m_loginBtn,SIGNAL(pressed()),this,SLOT(login()));
	setLayout(mbox);
	mbox->setMargin(0);

	
	QPalette  palette (this->palette());
	palette.setColor(QPalette::Background, Qt::white);
	this->setPalette( palette );
	
	
}

void UserLogindlg::closeWin()
{
	reject();
}

void UserLogindlg::doLogin(QString usr,QString pwd)
{
	m_md5pwd = pwd;
	m_usrAcc = usr;

	QString url = Configer::instance()->getUrl(); 
	if (url.isEmpty())
	{
		QMessageBox::information(this,("系统提示:"),("登录服务器地址为空，请检测配置!"));
		return;
	}

	QString userinfo = QString("?uname=%1&upwd=%2").arg(usr).arg(pwd);
	url += userinfo;

	QhttpNetwork::instance()->get(url);

}

void UserLogindlg::login()
{
	QString userAccount = m_userAccount->text();
	QString userPassword = m_userPassword->text();
	
	if (userAccount == "")
	{
		QMessageBox::information(this,("用户登录提示:"),("登录用户名为空,请输入用户名!"));
		return;
	}

	if (userPassword == "")
	{
		QMessageBox::information(this,("用户登录提示:"),("登录密码为空,请输入密码!"));
		return;
	}

	//对输入密码值进行Md5加密
	QByteArray byte_array;
	byte_array.append(userPassword);
	QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
	QString strpwdmd5 = hash_byte_array.toHex();

	doLogin(userAccount,strpwdmd5);

}

void UserLogindlg::loginResp(QByteArray resp)
{
	QString strrdata = QString::fromUtf8(resp.data());

	Json::Reader reader;
	Json::Value value;

	// 暂时先填0，表示成功，待接口修改后再改回默认值
	string status = "-1";
	m_vendorList.clear();

	string version = "";
	string filenames;// = "woodpecker_windows_386.exe,conf.ini,SfClient.exe,style.qss";
	string updateurl;//= "http://120.210.205.24/orderstres/sfAssistant/1.2.5/bin/";

	if(reader.parse(strrdata.toStdString(),value))
	{

		string success = value["success"].asString();
		if (success.length()>0)
		{
			return;
		}
		string siteId = value["siteId"].asString();
		Configer::instance()->setSiteId(siteId.c_str());

		string siteName = value["siteName"].asString();
		status = value["status"].asString();
		updateurl = value["updateUrl"].asString();
		version = value["version"].asString();
		const Json::Value arrayObj = value["vendors"];
		for (int i = 0;i<arrayObj.size();i++)
		{
			Vendors* vend = new Vendors;

			string vendorUrl = arrayObj[i]["vendorUrl"].asString();
			string vendorName = arrayObj[i]["vendorName"].asString();
			string vendorPassword = arrayObj[i]["vendorPassword"].asString();
			string vendorLoginName = arrayObj[i]["vendorLoginName"].asString();
			string factory = arrayObj[i]["factory"].asString();
			vend->vendorUrl = vendorUrl.c_str();
			vend->vendorName = vendorName.c_str();
			vend->vendorPassword = vendorPassword.c_str();
			vend->vendorLoginName = vendorLoginName.c_str();
			vend->vendorFactory = factory.c_str();
			m_vendorList.push_back(vend);
		}

		// 组成完整的updateurl
		const Json::Value arrayFiles = value["updateFiles"];
		if (arrayFiles.size()>0)
		{
			int idx = 0;
			string path = arrayFiles[idx]["filePath"].asString();
			idx = path.find_last_of("/");
			path = path.substr(0,idx+1);
			updateurl += path;
		}
		for (int i = 0;i<arrayFiles.size();i++)
		{

			filenames+=arrayFiles[i]["fileName"].asString();
			filenames += ",";
		}

		// 去掉最后一个逗号
		if (filenames.length()>0)
		{
			filenames = filenames.substr(0,filenames.length()-1);
		}

	}
	int rslt = atoi(status.c_str());
	
	switch(rslt)
	{
	case 0:

		m_loginOk = true;

		// 登录成功
		accept();

		// 保存用户名密码
		Configer::instance()->setPwd(m_md5pwd);
		Configer::instance()->setUser(m_usrAcc);

		// 检查是否需要更新
		if (versionCheck(version.c_str()))
		{
			QMessageBox::information(this,"系统提示","发现新版本，请立即升级");

			// 启动自动升级程序
			QProcess pro;
			QString program = "updater.exe";  
			QString appname = QCoreApplication::applicationName();

			QStringList arguments;  
			arguments << appname<<updateurl.c_str()<<filenames.c_str();  
			pro.start(program, arguments); 

			exit(0);
		}

		NetClient::instance()->init();

		break;
	case 1:
		// 表示用户名或密码错误
		QMessageBox::information(this,"系统提示","用户名或密码错误");
		break;
	case 2:
		break;
	default:
		break;

	}
}

void UserLogindlg::mousePressEvent(QMouseEvent *event)
{
	//只能是鼠标左键移动和改变大小
	if(event->button() == Qt::LeftButton) 
	{
		mouse_press = true;
	}

	//窗口移动距离
	move_point = event->globalPos() - pos(); 

}

void UserLogindlg::mouseReleaseEvent(QMouseEvent *event)
{
	mouse_press = false;
}

void UserLogindlg::mouseMoveEvent(QMouseEvent *event)
{
	//移动窗口
	if(mouse_press)   
	{
		QPoint move_pos = event->globalPos();
		move(move_pos - move_point);
	}
}

bool UserLogindlg::versionCheck(QString version)
{
	QString nowver = QCoreApplication::applicationVersion();

	qDebug("开始版本比较,本地版本:%s,服务器版本:%s",nowver.toStdString().c_str(),version.toStdString().c_str());
	QStringList sver = version.split(".");
	QStringList nver = nowver.split(".");

	if (sver.size()<3 || nver.size()<3)
	{
		return false;
	}

	int sv1 = sver[0].toInt();
	int sv2 = sver[1].toInt();
	int sv3 = sver[2].toInt();

	int nv1 = nver[0].toInt();
	int nv2 = nver[1].toInt();
	int nv3 = nver[2].toInt();

	if (sv1 > nv1)
	{
		return true;
	}
	else if(sv1 == nv1)
	{
		if (sv2>nv2)
		{
			return true;
		}
		else if (sv2 == nv2)
		{
			if (sv3>nv3)
			{
				return true;
			}
		}
	}

	return false;
}

