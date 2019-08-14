#include "mainwindow.h"
#include <string>
#include <QPushButton>
#include <QFileDialog>
#include <qfile.h>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include <QPalette>
#include <QColor>
#include "qhttp/QhttpNetwork.h"
#include "jsoncpp/json.h"
#include "gocontroller.h"
#include "titlewidget.h"
#include "netclient.h"
#include "configer.h"

#include <Windows.h>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	m_title = "工单助手";
	//m_audioOutput = NULL;
	m_sound = nullptr;

	// 一分钟一次心跳
	m_heartBeatTimer.setInterval(SF_HEARTBEAT_INTERVAL);
	m_woodpackerTimer.setInterval(SF_HEARTBEAT_INTERVAL);

	initWidget();
	initTray();

	//autoRun(false);
	int w = 880;
	int h = 500;
	int x = (QApplication::desktop()->width() - w)/2;
	int y = (QApplication::desktop()->height() - h)/2;
	
	setGeometry(QRect(x,y,w,h));
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle(m_title+"-v"+QCoreApplication::applicationVersion());

	connect(NetClient::instance(),SIGNAL(recvdata(int ,const char* ,int )),this,SLOT(recvdata(int ,const char* ,int )));
	connect(this,SIGNAL(finishPlay()),&m_playThread,SLOT(beginPlay()));
	connect(&m_playThread,SIGNAL(play(int)),this,SLOT(playSound(int)));
	connect(&m_heartBeatTimer,SIGNAL(timeout()),this,SLOT(sendHearBeat()));
	connect(&m_woodpackerTimer,SIGNAL(timeout()),this,SLOT(checkWoodPackerAlive()));

	// 启动语音队列线程
	m_playThread.start();
	m_woodpackerTimer.start();
}


void MainWindow::initWidget()
{
	QWidget * centralWdg = new QWidget;
	m_pLayout = new QVBoxLayout;
	m_pStackWdg = new QStackedWidget;
	m_pTitleWdg = new TitleWidget;
	m_pMainWdg = new MainWdg;
	centralWdg->setLayout(m_pLayout);
	m_pLayout->addWidget(m_pTitleWdg);
	m_pLayout->addWidget(m_pStackWdg);
	m_pStackWdg->addWidget(m_pMainWdg);
	m_pLayout->setMargin(0);
	setCentralWidget(centralWdg);

	m_status = new QLabel;
	QPalette statusPalette = m_status->palette();
	statusPalette.setColor(QPalette::WindowText,QColor(200,200,200));
	m_status->setPalette(statusPalette);
	QFont font;
	font.setPixelSize(12);
	m_status->setFont(font);
	m_status->setFrameStyle( QFrame::NoFrame); // 无边框
	m_status->setLineWidth(0);
	m_status->setStyleSheet("margin-left:8px;");
	m_status->setText(QString::fromLocal8Bit("就绪"));
	statusBar()->addWidget(m_status);
	statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	this->statusBar()->show();
}

void MainWindow::setVendorData(QList<Vendors*> vendorList)
{
	if(m_pMainWdg) {
		m_pMainWdg->setVendorList(vendorList);
	}
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


void MainWindow::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
}

void MainWindow::sysExit()
{
	int  ret = QMessageBox::question(this,"工单助手","是否确定退出工单助手?",QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		sendExit2WoodPack();
		NetClient::instance()->close();
		GoController::instance()->goExit();
		exit(0);
	}
	
}

void MainWindow::sendExit2WoodPack()
{
	QString json = "exit";
	QByteArray req ;
	req.append(json.toUtf8());
	QhttpNetwork::instance()->post(URL_EXIT,req);
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
		reg.setValue("sfclient","\"" + strAppPath + "\"");
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
	if (m_sound != nullptr)
	{
		delete m_sound;
		m_sound = nullptr;
	}
	keybd_event(VK_VOLUME_UP,MapVirtualKey(VK_VOLUME_UP,0),KEYEVENTF_EXTENDEDKEY,0); 
	keybd_event(VK_VOLUME_UP,MapVirtualKey(VK_VOLUME_UP,0),KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0); 

	m_sound = new QSound(sound);
	if (m_sound->isAvailable())
	{
		m_sound->play();
	}

	keybd_event(VK_VOLUME_DOWN,MapVirtualKey(VK_VOLUME_DOWN,0),KEYEVENTF_EXTENDEDKEY,0); 
	keybd_event(VK_VOLUME_DOWN,MapVirtualKey(VK_VOLUME_DOWN,0),KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP,0); 

	Sleep(6000);
	emit finishPlay();
	
}

void MainWindow::checkWoodPackerAlive()
{
	QProcess::ProcessState state = GoController::instance()->getState();
	if (state == QProcess::ProcessState::NotRunning)
	{
		this->showNormal();
		QMessageBox::warning(this,"系统提示","工单助手发生网络错误，请重新登录");
		NetClient::instance()->close();
		GoController::instance()->goExit();
		exit(0);
	}
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


void MainWindow::recvdata(int msgtype,const char* msg,int msglength)
{
	Q_UNUSED(msglength)
	switch (msgtype)
	{
	case SF_CMD_CONNECTED:
		m_status->setText(QString::fromLocal8Bit("成功连接服务器"));
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