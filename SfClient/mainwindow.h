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
#include "common.h"

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
public slots:

	void		uploadLog();
	void		sysExit();

	// 数据返回
	void		replyData(QByteArray data);

	//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		initWidget();
	//void		initToolBar();
	
	//void		initActions();
	//void		initConnections();
	//void		initMenu();
	void		initTray();
	void		autoRun(bool bAutoRun = true);
	void		checkLogin(Vendors* vend);
	void		updateLoginState(QString user);
	QToolButton*	tbFactory(QString btnName);
private:

	QString							m_title;
	/*QMenu*							m_fileMenu;
	QMenu*							m_helpMenu;
    QToolBar*						m_toolBar;
	QAction*						m_uploadLog;
	QAction*						m_exitAct;
	QAction*						m_onlineHelpAct;
	QAction*						m_authProAct;*/
	QTableWidget*					m_table;
	QSystemTrayIcon *				m_tray;		//托盘图标  
	QMenu *							m_tryMenu;	//托盘菜单  
	QAction *						m_reset;	//菜单实现功能：恢复窗口  
	QAction *						m_quit;		//菜单实现功能：退出程序  
	QList<Vendors*>					m_vendorList;
};

#endif // MAINWINDOW_H
