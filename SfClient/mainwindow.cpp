#include "mainwindow.h"
#include <string>
#include <QPushButton>
#include <QFileDialog>
#include <qfile.h>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include "qhttp/QhttpNetwork.h"
#include "jsoncpp/json.h"
#include "gocontroller.h"
#include "titlewidget.h"
#include "netclient.h"
#include "configer.h"

#include <Windows.h>


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),m_flogin(this)
{
	m_title = "思方工单助手";
	//m_audioOutput = NULL;
	m_sound = NULL;

	// 一分钟一次心跳
	m_heartBeatTimer.setInterval(SF_HEARTBEAT_INTERVAL);

	m_sesstionChecker.setInterval(SF_SESSIONCHER_INTERVAL);

	initWidget();
	initTray();

	autoRun();
	int w = 880;
	int h = 500;
	int x = (QApplication::desktop()->width() - w)/2;
	int y = (QApplication::desktop()->height() - h)/2;
	
	setGeometry(QRect(x,y,w,h));
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle(m_title+"-v"+QCoreApplication::applicationVersion());

	connect(NetClient::instance(),SIGNAL(recvdata(int ,const char* ,int )),this,SLOT(recvdata(int ,const char* ,int )));
	connect(QhttpNetwork::instance(),SIGNAL(response(QByteArray)),this,SLOT(replyData(QByteArray)));
	connect(this,SIGNAL(finishPlay()),&m_playThread,SLOT(beginPlay()));
	connect(&m_playThread,SIGNAL(play(int)),this,SLOT(playSound(int)));
	connect(&m_heartBeatTimer,SIGNAL(timeout()),this,SLOT(sendHearBeat()));
	connect(&m_sesstionChecker,SIGNAL(timeout()),this,SLOT(sesstionChecker()));
	connect(&m_flogin,SIGNAL(loginResp(Json::Value&)),this,SLOT(loginResp(Json::Value&)));
	connect(&m_flogin,SIGNAL(loging(int)),this,SLOT(loging(int)));

	// 启动语音队列线程
	m_playThread.start();

}


void MainWindow::initWidget()
{

	QVBoxLayout* vbox = new QVBoxLayout;
	
	TitleWidget * title = new TitleWidget();

	m_table = new QTableWidget;
	m_table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
	m_table->setColumnCount(4);
	QStringList headers;
	headers<<"厂家"<<"账号"<<"状态"<<"操作";
	m_table->setHorizontalHeaderLabels(headers);
	m_table->setFrameShape(QFrame::NoFrame);
	m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_table->setAlternatingRowColors(true);
	m_table->setStyleSheet("QTableWidget{alternate-background-color:#BBFFFF}");

	m_table->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
	m_table->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	m_table->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
	m_table->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);

	vbox->addWidget(title);
	vbox->addWidget(m_table);
	
	vbox->setMargin(0);
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(vbox);
	setCentralWidget(centralWidget);
	m_status = new QLabel;
	
	m_status->setFrameStyle( QFrame::NoFrame); // 无边框
	m_status->setLineWidth(0);
	m_status->setText("未知");
	statusBar()->addWidget(m_status);
	this->statusBar()->show();
}

void MainWindow::initList()
{
	m_table->setRowCount(m_vendorList.size());
	for (int i = 0;i<m_vendorList.size();i++)
	{
		int col = 0;
		Vendors* vend = m_vendorList.at(i);

		QTableWidgetItem* item = new QTableWidgetItem(vend->vendorName);
		item->setData(Qt::UserRole,vend->vendorFactory);
		m_table->setItem(i,col++,item);
		
		m_table->setItem(i,col++,new QTableWidgetItem(vend->vendorLoginName));

		m_table->setItem(i,col++,new QTableWidgetItem(""));
		
		// 美的厂家，手动登陆
		if (vend->vendorFactory == FACTORY_MEDIA)
		{
			QPushButton *btn = new QPushButton();
			btn->setProperty(PROPERTY_ROWNUM,i);
			btn->setProperty(PROPERTY_FACTORY,vend->vendorFactory);
			btn->setProperty(PROPERTY_USER,vend->vendorLoginName);
			btn->setProperty(PROPERTY_PWD,vend->vendorPassword);

			btn->setText("登陆");
			m_table->setCellWidget(i,col,btn);
			connect(btn,SIGNAL(pressed()),this,SLOT(onLogin()));
		}
		else
		{
			m_table->item(i,2)->setText("登录中...");
			
			Sleep(3000);
			checkLogin(vend);
			
		}
		
	}
}

void MainWindow::onLogin()
{
	QObject* obj = sender();
	if (obj != NULL)
	{
		int row = obj->property(PROPERTY_ROWNUM).toInt();
		QString factory = obj->property(PROPERTY_FACTORY).toString();
		QString user = obj->property(PROPERTY_USER).toString();
		QString pwd = obj->property(PROPERTY_PWD).toString();
		m_flogin.setContext(row,factory,user,pwd);
		
	}
	
	m_flogin.showDlg();

}

void MainWindow::loging(int row)
{
	QTableWidgetItem* item = m_table->item(row,2);
	if (item != NULL)
	{
		item->setText("登录中...");
		item->setTextColor(Qt::green);
	}
}

void MainWindow::checkLogin(Vendors* vend)
{
	QString json = QString("{\"user\":\"%1\",\"pwd\":\"%2\",\"factory\":\"%3\",\"mainServerHost\":\"%4\",\"statusReportHost\":\"%5\"}")
		.arg(vend->vendorLoginName)
		.arg(vend->vendorPassword)
		.arg(vend->vendorFactory)
		.arg(URL_MAIN_SERVER)
		.arg(URL_REPT);
	QByteArray req ;
	req.append(json);
	QhttpNetwork::instance()->post(URL_FACTORY_LONGIN,req);
	qDebug("向自动登录接口发送内容:%s",json.toStdString().c_str());
}

void MainWindow::setVendorData(QList<Vendors*> vendorList)
{
	m_vendorList = vendorList;
}


MainWindow::~MainWindow()
{
	NetClient::instance()->close();
}


QToolButton* MainWindow::tbFactory(QString btnName)
{
	QToolButton * btn = new QToolButton;
	btn->setText(btnName);
	btn->setIconSize(QSize(32,32));
	btn->setAutoRaise(true);
	btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	btn->setPopupMode(QToolButton::InstantPopup);
	return btn;
}

void MainWindow::uploadLog()
{
	QString url = "http://localhost:9100/CP_TEST/login.shtml";
	QByteArray req("{\"userid\":\"1538822184@qq.com\"}");
	QhttpNetwork::instance()->post(url,req);

}

void MainWindow::replyData(QByteArray data)
{
	QString msg = QString::fromUtf8(data.data());
	qDebug("[MainWindow->replyData] 接收返回: %s",msg.toStdString().c_str());

	Json::Reader reader;
	Json::Value value;

	
	if(reader.parse(msg.toStdString(),value))
	{
		
		string success = value["success"].asString();
		string status = value["status"].asString();
		

		if (status.length()>1)
		{
			parserSession(value);
			return;
		}
		// 过滤非本类型消息
		if (success.length()<=0)
		{
			return;
		}
		qDebug("收到厂家自动登录返回消息:%s",msg.toStdString().c_str());
		//m_vendorList.clear();
		int loginStatus;
		if (success == "true")
		{
			loginStatus = 1;
			qDebug()<<"厂家账号自动登录成功";
		}
		else
		{
			int code = 0;
			if (value["code"] != NULL)
			{
				code = value["code"].asInt();
			}
			
			loginStatus = code;
			qDebug("厂家账号自动登录失败,错误码:%d",code);
		}

		string user = value["user"].asString();
		updateLoginState(user.c_str(),loginStatus);

	}
}

void MainWindow::updateLoginState(QString user,int status)
{

	for (int i = 0;i<m_table->rowCount();i++)
	{
		QTableWidgetItem* itemUser = m_table->item(i,1);
		if (itemUser->text() == user)
		{
			QTableWidgetItem* itemState = m_table->item(i,2);
			
			switch (status)
			{
			case 1:
				itemState->setText("登陆成功");
				itemState->setTextColor(Qt::green);
				break;
			case 422:
				itemState->setText(ERROR_ALREADY_LONGIN);
				itemState->setTextColor(Qt::red);
				break;
			case 423:
				itemState->setText(ERROR_PWD);
				itemState->setTextColor(Qt::red);
				break;
			default:
				itemState->setText("登陆失败");
				itemState->setTextColor(Qt::red);
				break;
			}
		}
	}
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
}

void MainWindow::sysExit()
{
	int  ret = QMessageBox::question(this,"思方工单助手","是否确定退出思方工单助手?",QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		NetClient::instance()->close();
		GoController::instance()->goExit();
		exit(0);
	}
	
}

void MainWindow::initTray()
{
	//初始化托盘对象tray  
	m_tray = new QSystemTrayIcon(this);

	//设定托盘图标，引号内是自定义的png图片路径  
    m_tray->setIcon(QIcon(QPixmap(":/images/tray.png")));
	m_tray->setToolTip(m_title);

	//让托盘图标显示在系统托盘上  
    m_tray->show();

	//连接信号与槽，实现单击图标恢复窗口的功能，槽是自定义的槽  
    QObject::connect(m_tray,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(trayIconAction(QSystemTrayIcon::ActivationReason)));
  
   //***初始化托盘菜单及功能***  
    m_tryMenu = new QMenu(this);

	//初始化菜单  
    m_reset = new QAction(this);

	//初始化恢复窗口  
    m_reset->setText("显示窗口");  

	//菜单中的显示窗口，单击连接显示窗口  
    QObject::connect(m_reset,SIGNAL(triggered()),this,SLOT(showNormal()));
  
	//初始化退出程序  
    m_quit = new QAction(this);
    m_quit->setText("退出程序");  

	//菜单中的退出程序，单击连接退出</span>  
    QObject::connect(m_quit,SIGNAL(triggered()),this,SLOT(sysExit()));

    //qApp，是Qt自带的demo中的知识点，查了一下文档，qApp是Qt中所有app的指针，关闭它就可以关闭当前的程序</span>  
   //之所以不用this，close()，是由于软件要求关闭改为最小化到托盘，所以close()的功能已经不再是关闭窗口的功能，所以要另寻方法  
    //***将定义好的菜单加入托盘的菜单模块中***  
    m_tray->setContextMenu(m_tryMenu);  
    m_tryMenu->addAction(m_reset);  
    m_tryMenu->addAction(m_quit);  
}

//参数是Qt的保留字，表示对托盘图标的操作，该槽函数功能只实现了单击功能，可以实现其他功能比如双击、中击，具体可查文档或者Qt自带demo(关键字tray)  
void MainWindow::trayIconAction(QSystemTrayIcon::ActivationReason reason)  
{  
	if (reason==QSystemTrayIcon::Trigger)  
		this->showNormal();//如果对图标进行单击，则显示正常大小的窗口  
}  

void MainWindow::autoRun(bool bAutoRun)
{
	QSettings  reg("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);

	if (bAutoRun)
	{
		QString strAppPath=QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
		reg.setValue("sfclient",strAppPath);
	}
	else
	{
		reg.setValue("sfclient","");
	}

}

void MainWindow::playSound(int id)
{
	if (id>9 || id<0)
	{
		id = 0;
	}
	QString sound = QString("sound/tip%1.wav").arg(id);
	if (m_sound != NULL)
	{
		delete m_sound;
		m_sound = NULL;
	}
	m_sound = new QSound(sound);
	if (m_sound->isAvailable())
	{
		m_sound->play();
	}
	
	Sleep(6000);
	emit finishPlay();
	
}
void MainWindow::sendHearBeat()
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;

	person["userName"] = Configer::instance()->getUser().toStdString();
	person["siteId"] = Configer::instance()->getSiteId().toStdString();
	root.append(person);

	std::string json_file = writer.write(root);
	NetClient::instance()->sendData(SF_CMD_HEARTBEAT,json_file.c_str(),json_file.length());
}

void MainWindow::sendReg()
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;

	person["userName"] = Configer::instance()->getUser().toStdString();
	person["siteId"] = Configer::instance()->getSiteId().toStdString();
	root.append(person);

	std::string json_file = writer.write(root);
	NetClient::instance()->sendData(SF_CMD_REG,json_file.c_str(),json_file.length());
		
}

void MainWindow::loginResp(Json::Value& jvalue)
{
	string strRow = jvalue["seqno"].asString();
	int row = atoi(strRow.c_str());
	QTableWidgetItem* item = m_table->item(row,2);
	if (item == NULL)
	{
		return;
	}
	QWidget* btn = m_table->cellWidget(row,3);
	string sucess = jvalue["success"].asString();
	if (sucess == RESULT_TRUE)
	{
		// 登录成功
		
		item->setText("登录成功");
		item->setTextColor(Qt::green);
		
		if (!m_sesstionChecker.isActive())
		{
			// 启动sestion过期检查
			m_sesstionChecker.start();
		}
		
		if (btn != NULL)
		{
			btn->setEnabled(false);
		}
	}
	else
	{
		string code = jvalue["code"].asString();
		if (code == "c4")
		{
			item->setText(ERROR_PWD);
		}
		else if (code == "m3")
		{
			item->setText("验证码过期");
		}
		else if (code == "m4")
		{
			item->setText(" 验证码输入错误");
		}
		else if (code == "422")
		{
			item->setText(ERROR_ALREADY_LONGIN);
		}
		else
		{
			item->setText("登录失败");
		}
		item->setTextColor(Qt::red);

	}
}

void MainWindow::recvdata(int msgtype,const char* msg,int msglength)
{

	switch (msgtype)
	{
	case SF_CMD_CONNECTED:
		m_status->setText("成功连接服务器");
		sendReg();
		m_heartBeatTimer.start();
		break;
	case SF_CMD_DISCONNECTED:
		m_status->setText("服务器连接中断");
		break;

	case SF_CMD_PLAY_SOUND:
		parseTcpResponse(msg);
		qDebug(msg);
		break;
	case SF_CMD_REG:
		m_status->setText("注册成功");
		break;
	default:
		break;
	}
}

void MainWindow::parseTcpResponse(const char* msg)
{
	Json::Reader reader;
	Json::Value value;
	string js;
	js.append(msg);
	if(reader.parse(js,value))
	{
		string id  = value["category"].asString();
		m_playThread.enqueue(atoi(id.c_str()));
		
	}
}

void MainWindow::sesstionChecker()
{
	for (int i = 0;i<m_vendorList.size();i++)
	{
		Vendors * vend = m_vendorList.at(i);
		if (vend->vendorFactory == FACTORY_MEDIA)
		{
			sendSessionChecker(vend);
		}
	}
}

void MainWindow::parserSession(Json::Value & jvalue)
{
	string status = jvalue["status"].asString();
	if (!(status == RESULT_TRUE))
	{
		string user = jvalue["user"].asString();
		string factory = jvalue["factory"].asString();
		int row = m_table->rowCount();
		for (int i = 0;i<row;i++)
		{
			QTableWidgetItem* itemFactory = m_table->item(i,0);
			QTableWidgetItem* itemUser = m_table->item(i,1);
			string ftext = itemFactory->data(Qt::UserRole).toString().toStdString();
			string fuser = itemUser->text().toStdString();
			if (fuser == user && ftext == factory)
			{
				QTableWidgetItem* itemStatus = m_table->item(i,2);
				itemStatus->setText("会话过期，请重新登录");
				itemStatus->setTextColor(Qt::red);
				m_table->cellWidget(i,3)->setEnabled(true);
				
				// 显示窗口
				showNormal();
			}
		}
		if (factory == FACTORY_MEDIA)
		{
			// 清除sestion过期标志
			sendRmSessionTimeout(user.c_str());
		}
	}

}

void MainWindow::sendSessionChecker(Vendors *vender)
{
	QString json = QString("{\"user\":\"%1\",\"factory\":\"%2\"}")
		.arg(vender->vendorLoginName)
		.arg(vender->vendorFactory);
	QByteArray req ;
	req.append(json);
	QhttpNetwork::instance()->post(URL_SESSION_CHECK,req);
	qDebug("发送session过期检查命令:%s",json.toStdString().c_str());
}

void MainWindow::sendRmSessionTimeout(QString user)
{
	QString json = QString("{\"user\":\"%1\",\"factory\":\"%2\"}")
		.arg(user)
		.arg(FACTORY_MEDIA);
	QByteArray req ;
	req.append(json);
	QhttpNetwork::instance()->post(URL_REMOVE_SESSION_TIMEOUT,req);

	qDebug("发送session过期命令:%s",json.toStdString().c_str());
}
