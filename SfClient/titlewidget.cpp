#include "titlewidget.h"
#include "qhttp/QhttpNetwork.h"
#include "gocontroller.h"
TitleWidget::TitleWidget(QWidget* parent):QDialog(parent)
{
	
	initActions();
	initMenu();

	QHBoxLayout* hbox = new QHBoxLayout;
	QToolButton* fileBtn = tbFactory("文件");
	fileBtn->setIcon(QIcon(":/images/file.png"));
	fileBtn->setMenu(m_fileMenu);
	fileBtn->setObjectName("toolBtn");

	QToolButton* helpBtn = tbFactory("帮助");
	helpBtn->setIcon(QIcon(":/images/help.png"));
	helpBtn->setMenu(m_helpMenu);
	helpBtn->setObjectName("toolBtn");

	hbox->addWidget(fileBtn);
	hbox->addWidget(helpBtn);
	hbox->addStretch();
	setLayout(hbox);

	QPixmap pixmap = QPixmap(":images/top.png");
	QPalette  palette (this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette( palette );
	setAutoFillBackground(true);
	hbox->setMargin(0);
	setMinimumHeight(50);
}

QToolButton* TitleWidget::tbFactory(QString btnName)
{
	QToolButton * btn = new QToolButton;
	btn->setText(btnName);
	btn->setIconSize(QSize(32,32));
	btn->setAutoRaise(true);
	btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	btn->setPopupMode(QToolButton::InstantPopup);
	return btn;
}


void TitleWidget::initMenu()
{
	m_fileMenu = new QMenu;

	m_fileMenu->addAction(m_uploadLog);
	m_fileMenu->addAction(m_exitAct);

	m_helpMenu =new QMenu;
	m_helpMenu->addAction(m_onlineHelpAct);
	m_helpMenu->addAction(m_authProAct);

}


void TitleWidget::initActions()
{
	m_uploadLog = new QAction(QIcon(":images/upload.png"),"上传日志",this);
	m_exitAct = new QAction(QIcon(":images/exit.png"),"退出",this);
	m_onlineHelpAct = new QAction(QIcon(":/images/online.png"),"查看在线帮助",this);
	m_authProAct = new QAction(QIcon(":images/pro.png"),"管理授权协议",this);

	initConnections();
}

void TitleWidget::initConnections()
{
	connect(m_uploadLog,SIGNAL(triggered()),this,SLOT(uploadFile()));
	connect(m_authProAct,SIGNAL(triggered()),this,SLOT(proMgr()));
	connect(m_onlineHelpAct,SIGNAL(triggered()),this,SLOT(onlineHelp()));
	connect(m_exitAct,SIGNAL(triggered()),this,SLOT(sysExit()));
	
}

void TitleWidget::proMgr()
{

}

void TitleWidget::onlineHelp()
{
	QDesktopServices::openUrl(QUrl(QLatin1String("http://sifangerp.com/commonfiles/protocol.html")));
}

void TitleWidget::uploadFile()
{

}

void TitleWidget::sysExit()
{
	int  ret = QMessageBox::question(this,"思方工单助手","是否确定退出思方工单助手?",QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		GoController::instance()->goExit();
		exit(0);
	}
}