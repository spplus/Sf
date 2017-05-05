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
#include "widget.h"
#include "bri/quviccub.h"
#include "bri/BriChipErr.h"
#include "bri/BriSDKLib.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	MainWindow(QWidget* parent = NULL);
    ~MainWindow();

	//重写窗体关闭事件，关闭回到首页
	void		closeEvent(QCloseEvent *event);


signals:
	void		telephoneIn(QString telnum);

public slots:
	void		onOpen();
	void		onClose();

	void		sysExit();

	// 数据返回
	void		replyData(QByteArray data);

	// 处理来电事件
	void		dealIn(QString telnum);		

	//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		autoRun(bool bAutoRun = true);
	void		initTray();
	void		initWidget();
	void		initDevinfo();
	void		initChannel(int chID);
	void		appendInfo(QString msg);
	QString		getModule(int chID);
	QString		getDevType(long devtype);
	QString		getDevErrStr(long lResult);
	long		ProcessEvent(PBRI_EVENT pEvent);
	static BRIINT32	WINAPI ProcEventCallback(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32	lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx);

private:

	// 工单查询URL
	QString							m_queryUrl;

	// 连电号码
	QString							m_telnum;

	// 设备序列号
	BRIINT32						m_devnum;

	Widget							m_popuWin;
	QString							m_title;
	QTextEdit*						m_msg;

	QSystemTrayIcon *				m_tray;		//托盘图标  
	QMenu *							m_tryMenu;	//托盘菜单  
	QAction *						m_reset;	//菜单实现功能：恢复窗口  
	QAction *						m_quit;		//菜单实现功能：退出程序  
};

#endif // MAINWINDOW_H
