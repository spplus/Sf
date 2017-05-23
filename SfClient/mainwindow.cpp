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

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	m_title = "思方工单助手";
	
	initWidget();
	initTray();
	initMedia();

	autoRun();
	int w = 800;
	int h = 500;
	int x = (QApplication::desktop()->width() - w)/2;
	int y = (QApplication::desktop()->height() - h)/2;
	
	setGeometry(QRect(x,y,w,h));
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle(m_title+"-v"+QCoreApplication::applicationVersion());

	connect(NetClient::instance(),SIGNAL(recvdata(int ,const char* ,int )),this,SLOT(recvdata(int ,const char* ,int )));
	NetClient::instance()->init();

	
	connect(QhttpNetwork::instance(),SIGNAL(response(QByteArray)),this,SLOT(replyData(QByteArray)));
}

void MainWindow::initWidget()
{

	QVBoxLayout* vbox = new QVBoxLayout;
	
	TitleWidget * title = new TitleWidget();

	m_table = new QTableWidget;
	m_table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
	m_table->setColumnCount(3);
	QStringList headers;
	headers<<"厂家"<<"账号"<<"状态";
	m_table->setHorizontalHeaderLabels(headers);
	m_table->setFrameShape(QFrame::NoFrame);
	m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_table->setAlternatingRowColors(true);
	m_table->setStyleSheet("QTableWidget{alternate-background-color:#BBFFFF}");

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

		m_table->setItem(i,col++,new QTableWidgetItem(vend->vendorName));
		
		m_table->setItem(i,col++,new QTableWidgetItem(vend->vendorLoginName));

		m_table->setItem(i,col,new QTableWidgetItem("未知"));
		
		checkLogin(vend);
	}
}

void MainWindow::checkLogin(Vendors* vend)
{
	QString mainUrl = "http://www.sifangerp.com/mainserver/sfm/main/receiveOrders";
	QString reptUrl = "http://local.b";

	//QString url = "http://2ddeb837.ngrok.io/login";
	QString url = "http://localhost:8000/login";
	QString json = QString("{\"user\":\"%1\",\"pwd\":\"%2\",\"factory\":\"%3\",\"mainServerHost\":\"%4\",\"statusReportHost\":\"%5\"}")
		.arg(vend->vendorLoginName)
		.arg(vend->vendorPassword)
		.arg(vend->vendorFactory)
		.arg(mainUrl)
		.arg(reptUrl);
	QByteArray req ;
	req.append(json);
	QhttpNetwork::instance()->post(url,req);
}

void MainWindow::setVendorData(QList<Vendors*> vendorList)
{
	m_vendorList = vendorList;
}


MainWindow::~MainWindow()
{
	if (m_mediaObject != NULL)
	{
		m_mediaObject->clear();
		delete m_mediaObject;
		m_mediaObject = NULL;
	}
	if (m_audioOutput != NULL)
	{
		delete m_audioOutput;
		m_audioOutput = NULL;
	}
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
	qDebug("%s",msg);

	Json::Reader reader;
	Json::Value value;

	m_vendorList.clear();
	if(reader.parse(msg.toStdString(),value))
	{
		
		string success = value["success"].asString();
		
		// 过滤非本类型消息
		if (success.length()<=0)
		{
			return;
		}

		int loginStatus;
		if (success == "true")
		{
			loginStatus = 1;
		}
		else
		{
			loginStatus = 0;
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
			
			
			if (status == 1)
			{
				itemState->setText("登陆成功");
				itemState->setTextColor(Qt::green);
			}
			else
			{
				itemState->setText("登陆失败");
				itemState->setTextColor(Qt::red);
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
		//strAppPath.replace(QChar('/'),QChar('\\'),Qt::CaseInsensitive);
		reg.setValue("sfclient",strAppPath);
	}
	else
	{
		reg.setValue("sfclient","");
	}

}

void MainWindow::initMedia()
{
	m_mediaObject = new Phonon::MediaObject(this);
	m_audioOutput =
		new Phonon::AudioOutput(Phonon::VideoCategory, this);
	Phonon::createPath(m_mediaObject, m_audioOutput);
	Phonon::MediaSource source("sound/tip.mp3");
	m_mediaObject->setCurrentSource(source);
}

void MainWindow::sendReg()
{
	Json::Value root;
	Json::FastWriter writer;
	Json::Value person;

	/*
	{
	"userName":"abc",
	"siteId":"abcdefg"
	}
	*/

	person["userName"] = Configer::instance()->getUser().toStdString();
	person["siteId"] = Configer::instance()->getSiteId().toStdString();
	root.append(person);

	std::string json_file = writer.write(root);

	NetClient::instance()->sendData(SF_CMD_REG,json_file.c_str(),json_file.length());
}

void MainWindow::recvdata(int msgtype,const char* msg,int msglength)
{
	switch (msgtype)
	{
	case SF_CMD_CONNECTED:
		m_status->setText("成功连接服务器");
		sendReg();

		break;
	case SF_CMD_DISCONNECTED:
		m_status->setText("服务器连接中断");
		break;

	case SF_CMD_PLAY_SOUND:
		m_mediaObject->play();
		break;
	default:
		break;
	}
}