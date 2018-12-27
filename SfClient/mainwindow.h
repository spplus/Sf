#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtoolbar.h>
#include <qaction.h>
#include <QMenu>
#include <QMenuBar>
#include <QSplitter>
#include <qtimer.h>
#include <QtGui>
#include <QSound>
#include <QVBoxLayout>

#include "common.h"
#include "playthread.h"
#include "factorylogin.h"
#include "mainwdg.h"
#include "titlewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	MainWindow(QWidget* parent = NULL);
    ~MainWindow();

public:
	void		initList();

	//重写窗体关闭事件，关闭回到首页

	void		closeEvent(QCloseEvent *event);
	void		setVendorData(QList<Vendors*> vendorList);

signals:
	void		finishPlay();

public slots:
	// 登录中
	void		uploadLog();
	void		sysExit();
	void		playSound(int id);
	void		sendHearBeat();

	// TCP服务器数据返回
	void		recvdata(int msgtype,const char* msg,int msglength);

	//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		initWidget();
	void		initTray();
	void		parseTcpResponse(const char* msg);

	// 发送注册信息
	void		sendReg();
	void		autoRun(bool bAutoRun = false);
	void		updateLoginState(QString user,int status);
	QToolButton*	tbFactory(QString btnName);
private:
	TitleWidget*					m_pTitleWdg;
	MainWdg*						m_pMainWdg;
	QVBoxLayout*					m_pLayout;
	QStackedWidget*					m_pStackWdg;

	QSound*							m_sound;
	QLabel*							m_status;
	QString							m_title;
	QTableWidget*					m_table;
	QSystemTrayIcon *				m_tray;		//托盘图标  
	QMenu *							m_tryMenu;	//托盘菜单  
	QAction *						m_reset;	//菜单实现功能：恢复窗口  
	QAction *						m_quit;		//菜单实现功能：退出程序  
	QTimer							m_heartBeatTimer;
	QList<Vendors*>					m_vendorList;
	PlayThread						m_playThread;
};

#endif // MAINWINDOW_H
