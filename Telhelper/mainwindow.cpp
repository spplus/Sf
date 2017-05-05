#include "mainwindow.h"
#include <string>
#include <QPushButton>
#include <QFileDialog>
#include <qfile.h>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>


using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	m_title = "思方电话助手";
	initWidget();
	initTray();
	autoRun();
	int w = 800;
	int h = 500;
	int x = (QApplication::desktop()->width() - w)/2;
	int y = (QApplication::desktop()->height() - h)/2;
	
	setGeometry(QRect(x,y,w,h));
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle(m_title+"-v"+QCoreApplication::applicationVersion());

	connect(this,SIGNAL(telephoneIn(QString)),this,SLOT(dealIn(QString)));

}


void MainWindow::closeEvent(QCloseEvent *event)
{
	hide();//隐藏窗口  
	event->ignore();//忽略关闭事件  
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
    m_reset->setText("显示");  

	//菜单中的显示窗口，单击连接显示窗口  
    QObject::connect(m_reset,SIGNAL(triggered()),this,SLOT(showNormal()));
  
	//初始化退出程序  
    m_quit = new QAction(this);
    m_quit->setText("退出");  

	//菜单中的退出程序，单击连接退出</span>  
    QObject::connect(m_quit,SIGNAL(triggered()),this,SLOT(sysExit()));

    //qApp，是Qt自带的demo中的知识点，查了一下文档，qApp是Qt中所有app的指针，关闭它就可以关闭当前的程序</span>  
   //之所以不用this，close()，是由于软件要求关闭改为最小化到托盘，所以close()的功能已经不再是关闭窗口的功能，所以要另寻方法  
    //***将定义好的菜单加入托盘的菜单模块中***  
    m_tray->setContextMenu(m_tryMenu);  
    m_tryMenu->addAction(m_reset);  
    m_tryMenu->addAction(m_quit);  
}


void MainWindow::sysExit()
{
	int  ret = QMessageBox::question(this,m_title,"是否确定退出思方电话助手?",QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		onClose();
		exit(0);
	}

}

void MainWindow::initWidget()
{

	QVBoxLayout* vbox = new QVBoxLayout;
	QHBoxLayout* hbox = new QHBoxLayout;
	QPushButton* openBtn = new QPushButton("打开");
	QPushButton* closeBtn = new QPushButton("关闭");

	hbox->addWidget(openBtn);
	hbox->addWidget(closeBtn);
	hbox->addStretch();

	m_msg = new QTextEdit;
	m_msg->setReadOnly(true);
	vbox->addLayout(hbox);
	vbox->addWidget(m_msg);
	
	vbox->setMargin(0);
	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(vbox);
	setCentralWidget(centralWidget);

	connect(openBtn,SIGNAL(pressed()),this,SLOT(onOpen()));
	connect(closeBtn,SIGNAL(pressed()),this,SLOT(onClose()));
}



MainWindow::~MainWindow()
{
	onClose();
}

void MainWindow::dealIn(QString telnum)
{
	int idx = telnum.lastIndexOf("=");
	telnum = telnum.right(telnum.length()-idx-1);

	QString content = "连电号码:"+telnum;

	QString url = "http://www.baidu.com";
	m_popuWin.setMsg(m_title,content,url);
	m_popuWin.showAsQQ();
}


void MainWindow::onOpen()
{
	long lRet = QNV_OpenDevice(ODT_LBRIDGE,0,0);
	if(lRet == ERROR_INVALIDDLL)
	{
		QMessageBox::warning(this,"系统提示","DLL不合法");
	}
	else if(lRet <= 0 || QNV_DevInfo(0,QNV_DEVINFO_GETCHANNELS) <= 0)
	{
		QMessageBox::warning(this,"系统提示","打开设备失败,请检查设备是否已经插入并安装了驱动,并且没有其它程序已经打开设备");
	}
	else
	{
		QString strFileVersion = (char*)QNV_DevInfo(0,QNV_DEVINFO_FILEVERSION);
		QString strMsg = QString("打开设备成功(2.16/%1) 通道数=%2 设备数=%3").arg(strFileVersion).arg(QNV_DevInfo(0,QNV_DEVINFO_GETCHANNELS)).arg(QNV_DevInfo(0,QNV_DEVINFO_GETCHIPS));
		appendInfo(strMsg);

		initDevinfo();
	}
}

void MainWindow::onClose()
{
	if(QNV_CloseDevice(ODT_ALL,0) != 0)
	{
		appendInfo("关闭设备成功");
	}
	else
	{
		appendInfo("关闭设备失败");
	}
}

void MainWindow::appendInfo(QString msg)
{
	m_msg->append(msg);
}


void MainWindow::initChannel(int chID)
{
	QNV_Event(chID,QNV_EVENT_REGCBFUNC,(DWORD)this,(char*)ProcEventCallback,NULL,0);
}

void MainWindow::initDevinfo()
{
	for(BRIINT16 i=0;i<QNV_DevInfo(-1,QNV_DEVINFO_GETCHANNELS);i++)
	{
		
		//pChannel->SetChannelCtrlID(i);
		initChannel(i);
		m_devnum = QNV_DevInfo(i,QNV_DEVINFO_GETSERIAL);
		QString str = QString("通道ID=%1 设备ID=%2 序列号=%3 设备类型=%4 芯片类型=%5 模块=%6").arg(i)
			.arg(QNV_DevInfo(i,QNV_DEVINFO_GETDEVID))
			.arg(m_devnum)
			.arg(getDevType(QNV_DevInfo(i,QNV_DEVINFO_GETTYPE)))
			.arg(QNV_DevInfo(i,QNV_DEVINFO_GETCHIPTYPE))
			.arg(getModule(i));
			
		appendInfo(str);
	}
}

QString MainWindow::getModule(int chID)
{
	QString strModule,str;
	long lModule=QNV_DevInfo(chID,QNV_DEVINFO_GETMODULE);
	str = QString("(0x%1)/").arg(lModule);
	strModule+=str;
	if(lModule&DEVMODULE_DOPLAY) strModule+="有喇叭/";
	if(lModule&DEVMODULE_CALLID) strModule+="有来电显示/";
	if(lModule&DEVMODULE_PHONE) strModule+="话机拨号/";
	if(lModule&DEVMODULE_SWITCH) strModule+="断开电话机,接收话机按键/";
	if(lModule&DEVMODULE_PLAY2TEL) strModule+="播放语音到电话机/";
	if(lModule&DEVMODULE_HOOK) strModule+="软摘机/";
	if(lModule&DEVMODULE_MICSPK) strModule+="有耳机/MIC/";
	if(lModule&DEVMODULE_RING) strModule+="模拟话机震铃/";
	if(lModule&DEVMODULE_STORAGE) strModule+="FLASH数据存储/";
	if(lModule&DEVMODULE_FAX) strModule+="收发传真/";
	if(lModule&DEVMODULE_POLARITY) strModule+="反级检测/";	
	return strModule;
}

QString MainWindow::getDevType(long lDevType)
{
	QString str;
	str = QString("0x%1").arg(lDevType);
	switch(lDevType)
	{
	case DEVTYPE_T1:str+="(cc301 T1)";break;
	case DEVTYPE_T2:str+="(cc301 T2)";break;
	case DEVTYPE_T3:str+="(cc301 T3)";break;
	case DEVTYPE_T4:str+="(cc301 T4)";break;	
	case DEVTYPE_T5:str+="(cc301 T5)";break;
	case DEVTYPE_T6:str+="(cc301 T6)";break;	
	case DEVTYPE_IR1:str+="(cc301 IR1)";break;
	case DEVTYPE_ID1:str+="(cc301 ID1)";break;
	case DEVTYPE_IP1:str+="(cc301 IP1)";break;
	case DEVTYPE_IA1:str+="(cc301 IA1)";break;
	case DEVTYPE_IA2:str+="(cc301 IA2)";break;
	case DEVTYPE_IA3:str+="(cc301 IA3)";break;
	case DEVTYPE_IA4:str+="(cc301 IA4)";break;
	case DEVTYPE_IB1:str+="(cc301 IB1)";break;
	case DEVTYPE_IB2:str+="(cc301 IB2)";break;
	case DEVTYPE_IB3:str+="(cc301 IB3)";break;
	case DEVTYPE_IB4:str+="(cc301 IB4)";break;
	case DEVTYPE_IP1_F:str+="(cc301 IP1_F)";break;
	case DEVTYPE_IA4_F:str+="(cc301 IA4_F)";break;
	case DEVTYPE_IC2_R:str+="(cc301 IC2_R)";break;
	case DEVTYPE_IC2_LP:str+="(cc301 IC2_LP)";break;
	case DEVTYPE_IC2_LPQ:str+="(cc301 IC2_LPQ)";break;
	case DEVTYPE_IC2_LPF:str+="(cc301 IC2_LPF)";break;
	case DEVTYPE_IC4_R:str+="(cc301 IC4_R)";break;
	case DEVTYPE_IC4_LP:str+="(cc301 IC4_LP)";break;
	case DEVTYPE_IC4_LPQ:str+="(cc301 IC4_LPQ)";break;
	case DEVTYPE_IC4_LPF:str+="(cc301 IC4_LPF)";break;
	case DEVTYPE_IC7_R:str+="(cc301 IC7_R)";break;
	case DEVTYPE_IC7_LP:str+="(cc301 IC7_LP)";break;
	case DEVTYPE_IC7_LPQ:str+="(cc301 IC7_LPQ)";break;
	case DEVTYPE_IC7_LPF:str+="(cc301 IC7_LPF)";break;
	case DEVTYPE_A1:str+="(玻瑞器 A1)";break;
	case DEVTYPE_A2:str+="(玻瑞器 A2)";break;
	case DEVTYPE_A3:str+="(玻瑞器 A3)";break;
	case DEVTYPE_A4:str+="(玻瑞器 A4)";break;
	case DEVTYPE_B1:str+="(玻瑞器 B1)";break;
	case DEVTYPE_B2:str+="(玻瑞器 B2)";break;
	case DEVTYPE_B3:str+="(玻瑞器 B3)";break;
	case DEVTYPE_B4:str+="(玻瑞器 B4)";break;
	case DEVTYPE_C4_L:str+="(玻瑞器 C4-L)";break;
	case DEVTYPE_C4_P:str+="(玻瑞器 C4-P)";break;
	case DEVTYPE_C4_LP:str+="(玻瑞器 C4-LP)";break;
	case DEVTYPE_C4_LPQ:str+="(玻瑞器 C4-LPQ)";break;
	case DEVTYPE_C7_L:str+="(玻瑞器 C7-L)";break;
	case DEVTYPE_C7_P:str+="(玻瑞器 C7-P)";break;
	case DEVTYPE_C7_LP:str+="(玻瑞器 C7-LP)";break;
	case DEVTYPE_C7_LPQ:str+="(玻瑞器 C7-LPQ)";break;
	case DEVTYPE_R1:str+="(玻瑞器 R1)";break;
	case DEVTYPE_C4_R:str+="(玻瑞器 C4-R)";break;
	case DEVTYPE_C7_R:str+="(玻瑞器 C7-R)";break;
	default:
		{
		}break;
	}
	return str;
}

BRIINT32	WINAPI MainWindow::ProcEventCallback(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32 lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx)
{
	MainWindow *p=(MainWindow *)dwUserData;
	BRI_EVENT ev={0};	
	ev.uChannelID = uChannelID;
	ev.lEventType = lType;
	ev.lEventHandle=lHandle;
	ev.lParam=lParam;
	ev.lResult=lResult;
	memcpy(ev.szData,pData,sizeof(ev.szData));
	memcpy(ev.szDataEx,pDataEx,sizeof(ev.szDataEx));	
	return p->ProcessEvent(&ev);
}

long MainWindow::ProcessEvent(PBRI_EVENT pEvent)
{
		int m_nChannelID = pEvent->uChannelID;

		QString str,strValue = QString("Handle=%1 Result=%2 Data=%3").arg(pEvent->lEventHandle).arg(pEvent->lResult).arg(pEvent->szData);
		switch(pEvent->lEventType)
		{
		case BriEvent_PhoneHook:
			{
				str = QString("通道%1: 电话机摘机").arg(m_nChannelID+1);
			}break;
		case BriEvent_PhoneHang:
			{
				str = QString("通道%1: 电话机挂机").arg(m_nChannelID+1);
			}break;
		case BriEvent_CallIn:
			str = QString("通道%1: 来电响铃 %2").arg(m_nChannelID+1).arg(strValue);
			break;
		case BriEvent_GetCallID:
			{
				long lSerial=QNV_DevInfo(m_nChannelID,QNV_DEVINFO_GETSERIAL);
				str = QString("通道%1: 接收到来电号码 %2").arg(m_nChannelID+1).arg(strValue);

				emit telephoneIn(strValue);
			}break;
		case BriEvent_StopCallIn:
			str = QString("通道%1: 停止呼入,产生一个未接电话 %2").arg(m_nChannelID+1).arg(strValue);
			break;
		case BriEvent_DialEnd:
			{
				if(QNV_GetDevCtrl(pEvent->uChannelID,QNV_CTRL_PHONE) > 0)
				{
					//QNV_SetDevCtrl(m_nChannelID,QNV_CTRL_DOHOOK,0);//电话机已经拿着可以考虑自动软挂机,避免3方通话状态，话机里有背景音出现
				}
				str = QString("通道%1: 拨号结束 %2").arg(m_nChannelID+1).arg(strValue);
			}break;
		
		case BriEvent_RefuseEnd:
			str = QString("通道%1: 拒接来电完成 %2").arg(m_nChannelID+1).arg(strValue);break;	
		
		case BriEvent_CheckLine:
			{
				if(pEvent->lResult & CHECKLINE_MASK_DIALOUT)
				{
					str = QString("通道%1: [ok]***线路拨号音正常,能正常软拨号***-----------------").arg(m_nChannelID+1);					
				}else
				{
					str = QString("通道%1: [err]线路拨号音不正常,可能不能正常软拨号，检查LINE口线路!!!").arg(m_nChannelID+1);
					//AfxMessageBox(str);
				}					
				
				if(pEvent->lResult & CHECKLINE_MASK_REV)
				{
					str = QString("通道%1: [ok]***线路LINE口/PHONE口未接反***----------------------").arg(m_nChannelID+1);					
				}
				else
				{
					str = QString("通道%1: [err]线路LINE口/PHONE口可能接反了").arg(m_nChannelID+1);
					
				}
			}break;
		case BriEvent_DevErr:
			{
				str = QString("通道%1: 设备发生错误！原因=%2(%3/%4) %5").arg(m_nChannelID+1).arg(getDevErrStr(pEvent->lResult)).arg((atol(pEvent->szData)&0xFF00)>>8).arg((atol(pEvent->szData)&0xFF)).arg(strValue);				
				
			}break;
		case BriEvent_PlugOut:
			{
				str = QString("通道%1: 设备被拔掉").arg(m_nChannelID+1);				
			}break;
		
	
	
		default:
			{
				str = QString("通道%1: 其它忽略事件 eventid=%2 lResult=%3 szData=%4").arg(m_nChannelID+1).arg(pEvent->lEventType).arg(pEvent->lResult).arg(pEvent->szData);
			}break;
		}
		if(!str.isEmpty())
		{
			appendInfo(str);
		}
		
		return 1;
}


QString	MainWindow::getDevErrStr(long lResult)
{
	switch(lResult)
	{
	case 0:return "读取数据错误";
	case 1:return "写入数据错误";
	case 2:return "数据帧ID丢失,可能是CPU太忙";
	case 3:return "设备已经被拔掉";
	case 4:return "序列号冲突";
	default:return "未知错误";
	}
	return "";
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
		reg.setValue("telhelper",strAppPath);
	}
	else
	{
		reg.setValue("telhelper","");
	}

}