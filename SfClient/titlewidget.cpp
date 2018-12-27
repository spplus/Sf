#include "titlewidget.h"
#include "qhttp/QhttpNetwork.h"
#include "gocontroller.h"
#include "jsoncpp/json.h"
#include "netclient.h"
#include "configer.h"
#include "common.h"
#include <QDebug>
#include <QDir>

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
	setFixedHeight(23.3);
}

QToolButton* TitleWidget::tbFactory(QString btnName)
{
	QToolButton * btn = new QToolButton;
	btn->setText(btnName);
	btn->setIconSize(QSize(20,20));
	btn->setAutoRaise(true);
	btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	btn->setPopupMode(QToolButton::InstantPopup);
	btn->setStyleSheet("QToolButton::menu-indicator{image:none;} QToolButton:hover {background-color:rgb(242,242,242);color:rgb(16,16,16)} QToolButton:pressed");
	return btn;
}


void TitleWidget::initMenu()
{
	m_fileMenu = new QMenu;
	//m_fileMenu->addAction(m_uploadLog);
	//m_fileMenu->addAction(m_settings);
	m_fileMenu->addAction(m_exitAct);

	m_helpMenu =new QMenu;
	//m_helpMenu->addAction(m_onlineHelpAct);
	m_helpMenu->addAction(m_authProAct);

}

void TitleWidget::setSettingActionName(QString name) {
	m_settings->setText(name);
}

QString TitleWidget::getSettingActionName() {
	return m_settings->text();
}

void TitleWidget::initActions()
{
	m_uploadLog = new QAction(QIcon(":images/upload.png"),"上传日志",this);
	m_settings = new QAction("账号维护",this);
	m_exitAct = new QAction(QIcon(":images/exit.png"),"退出",this);
	m_onlineHelpAct = new QAction(QIcon(":/images/online.png"),"查看在线帮助",this);
	m_authProAct = new QAction(QIcon(":images/pro.png"),"管理授权协议",this);

	initConnections();
}

void TitleWidget::initConnections()
{
	connect(m_uploadLog,SIGNAL(triggered()),this,SLOT(uploadFile()));
	connect(m_settings,SIGNAL(triggered()),this,SLOT(settingsActionClicked()));
	connect(m_authProAct,SIGNAL(triggered()),this,SLOT(proMgr()));
	connect(m_onlineHelpAct,SIGNAL(triggered()),this,SLOT(onlineHelp()));
	connect(m_exitAct,SIGNAL(triggered()),this,SLOT(sysExit()));
}

void TitleWidget::proMgr()
{
	QString path = QString(QDir::currentPath()+"/protocal.html");
	qDebug() << path;
	QDesktopServices::openUrl(QUrl(path,QUrl::TolerantMode));
}

void TitleWidget::onlineHelp()
{
	/*QDesktopServices::openUrl(QUrl(QLatin1String("http://sifangerp.com/commonfiles/protocol.html")));*/
}

void TitleWidget::uploadFile()
{

	NetClient::instance()->close();
	
}

void TitleWidget::sysExit()
{
	int  ret = QMessageBox::question(this,"工单助手","是否确定退出工单助手?",QMessageBox::Yes|QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		NetClient::instance()->close();
		GoController::instance()->goExit();
		exit(0);
	}
}

void TitleWidget::settingsActionClicked() {
	emit settingsActionClickedSignal();
}	