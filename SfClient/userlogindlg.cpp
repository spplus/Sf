#include <string>

#include "userlogindlg.h"
#include "qhttp/qhttpnetwork.h"
#include "jsoncpp/json.h"
#include "configer.h"
#include "topwidget.h"
#include "netclient.h"
#include "gocontroller.h"
#include "factorydb.h"

using namespace std;

UserLogindlg::UserLogindlg()
	: QDialog(),
	m_vendorList()
{
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
	this->resize(600,440);
	setAutoFillBackground(true);
	setWindowIcon(QIcon(":images/tray.png"));

	//初始化为未按下鼠标左键
	mouse_press = false;

	iniUi();
	m_loginOk = false;
	m_ndmd5 = true;
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

	m_vendorList.clear();
}

void UserLogindlg::passwdChanged(const QString &text)
{
	Q_UNUSED(text)
	m_ndmd5 = true;	
}

void UserLogindlg::setUserInfo(QString usr,QString pwd)
{
	m_ndmd5 = false;
	m_userAccount->setText(usr);
	m_userPassword->setText("1234567890");
	m_userPassword->setProperty("pwd",pwd);
	connect(m_userPassword,SIGNAL(textChanged(const QString &)),this,SLOT(passwdChanged(const QString &)));
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
	
	QString strpwdmd5 = userPassword;

	if (m_ndmd5)
	{
		//对输入密码值进行Md5加密
		QByteArray byte_array;
		byte_array.append(userPassword);
		QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
		strpwdmd5 = hash_byte_array.toHex();
	}
	else
	{
		strpwdmd5 = m_userPassword->property("pwd").toString();
	}
	Configer::instance()->setUser(userAccount);
	doLogin(userAccount,strpwdmd5);

}

void UserLogindlg::loginResp(QByteArray resp)
{
	QString strrdata = QString::fromUtf8(resp.data());
	qDebug() << strrdata;

	Json::Reader reader;
	Json::Value value;

	// 暂时先填0，表示成功，待接口修改后再改回默认值
	string status = "-1";
	//m_vendorList.clear();

	string version = "";
	string filenames;
	string updateurl;
	
	if(reader.parse(strrdata.toStdString(),value))
	{
		string success = value["success"].asString();
		if (success.length()>0)
		{
			return;
		}
		status = value["status"].asString();
		string siteId = value["siteId"].asString();
		string userType = value["userType"].asString();
		if (siteId.length() <= 0 && status != "1")
		{
			return;
		}

		Configer::instance()->setSiteId(siteId.c_str());
		Configer::instance()->setUserType(QString(userType.c_str()));

		string siteName = value["siteName"].asString();
		
		updateurl = value["updateUrl"].asString();
		version = value["version"].asString();
		const Json::Value arrayObj = value["vendors"];

		auto *db = new FactoryDB;
		db->clearFactory();
		for (unsigned int i = 0; i < arrayObj.size();i++)
		{
			string vendorUrl = arrayObj[i]["vendorUrl"].asString();
			string vendorName = arrayObj[i]["vendorName"].asString();
			string vendorPassword = arrayObj[i]["vendorPassword"].asString();
			string vendorLoginName = arrayObj[i]["vendorLoginName"].asString();
			string factory = arrayObj[i]["factory"].asString();
			string id = arrayObj[i]["vendorAccountId"].asString();

			Vendors* vendors = new Vendors;
			vendors->sfAccount = Configer::instance()->getUser();
			vendors->vendorFactory = QString(factory.c_str());
			vendors->vendorLoginName = QString(vendorLoginName.c_str());
			vendors->vendorName = QString(vendorName.c_str());
			vendors->vendorPassword = QString(vendorPassword.c_str());
			vendors->vendorUrl = QString(vendorUrl.c_str());
			vendors->serverId = QString(id.c_str());
			
			db->insertFactory(vendors);
			m_vendorList.append(vendors);
		}
		delete db;

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
		for (uint i = 0;i < arrayFiles.size();i++)
		{
			filenames+=arrayFiles[i]["fileName"].asString();
			filenames += ",";
		}

		// 去掉最后一个逗号
		if (filenames.length()>0)
		{
			filenames = filenames.substr(0,filenames.length()-1);
		}

	}else{
		QMessageBox::warning(this,"系统提示","解析登录报文错误");
		qDebug() << "解析登录报文错误";
		qDebug() << reader.getFormatedErrorMessages().c_str();
	;
	}
	int rslt = atoi(status.c_str());
	
	switch(rslt)
	{
	case 0:

		m_loginOk = true;

		// 保存用户名密码
		Configer::instance()->setPwd(m_md5pwd);
		Configer::instance()->setUser(m_usrAcc);
		

		// 检查是否需要更新
		if (versionCheck(version.c_str()))
		{
			QMessageBox::information(this,"系统提示","发现新版本，请立即升级");
			// 退出go
			GoController::instance()->goExit();

			// 启动自动升级程序
			QProcess pro;
			QString program = "updater.exe";  
			QString appname = QCoreApplication::applicationName();

			QStringList arguments;  
			arguments << appname<<updateurl.c_str()<<filenames.c_str();  
			pro.start(program, arguments); 

			exit(0);
		}
		// 连接TCP服务器
		NetClient::instance()->init();
		
		// 登录成功
		accept();
		break;
	case 1:
		// 表示用户名或密码错误
		QMessageBox::information(this,"系统提示","用户名或密码错误");
		break;
	case 425:
		QMessageBox::information(this,"系统提示","暂停支持");
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
	Q_UNUSED(event)
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

