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

#include "common.h"
#include "playthread.h"
#include "factorylogin.h"

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
	void		loging(int row);
	void		uploadLog();
	void		sysExit();
	void		onLogin();
	void		playSound(int id);

	// WD登录接口返回
	void		loginResp(Json::Value& jvalue);

	// 数据返回
	void		replyData(QByteArray data);

	void		sendHearBeat();

	// sesstion过期检查
	void		sesstionChecker();

	// TCP服务器数据返回
	void		recvdata(int msgtype,const char* msg,int msglength);

	//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		parserSession(Json::Value & jvalue);
	void		initWidget();
	void		initTray();
	void		sendSessionChecker(Vendors *vender);
	void		parseTcpResponse(const char* msg);
	void		sendRmSessionTimeout(QString user);

	// 发送注册信息
	void		sendReg();
	void		autoRun(bool bAutoRun = true);
	void		checkLogin(Vendors* vend);
	void		updateLoginState(QString user,int status);
	QToolButton*	tbFactory(QString btnName);
private:

	QSound*							m_sound;
	QLabel*							m_status;
	QString							m_title;
	QTableWidget*					m_table;
	QSystemTrayIcon *				m_tray;		//托盘图标  
	QMenu *							m_tryMenu;	//托盘菜单  
	QAction *						m_reset;	//菜单实现功能：恢复窗口  
	QAction *						m_quit;		//菜单实现功能：退出程序  
	QTimer							m_heartBeatTimer;
	QTimer							m_sesstionChecker;
	QList<Vendors*>					m_vendorList;
	PlayThread						m_playThread;
	FactoryLogin					m_flogin;
};

#endif // MAINWINDOW_H
