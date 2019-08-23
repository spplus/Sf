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
#include <QWebView>
#include "widget.h"
#include "spwebview.h"
#include "bri/quviccub.h"
#include "bri/BriChipErr.h"
#include "bri/BriSDKLib.h"
#include "maincontroller.h"


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
	void		openUrl(QString url);
	void		sysExit();
	void		showSetting();
	void		openAudioDir();
	void		appendInfo(QString msg);

	// 数据返回
	void		replyData(QByteArray data);

	// 处理来电事件
	void		dealIn(QString telnum);		

	//对托盘图标操作的槽：本代码实现单机图标恢复窗口功能 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		mkdir();
	void		reStart();
	void		telOut(QString svalue);
	void		startRecAudio();
	void		stopRecAudio();
	void		autoRun(bool bAutoRun = true);
	void		initTray();
	void		initWidget();
	void		initDevinfo();
	void		requestVersion();
	void		needUpdate(QString version,QString updateUrl,QString fileList);
	bool		versionCheck(QString version);
	void		initChannel(int chID);
	
	
	QString		getCurDateTime(QString fmt="yyyy-MM-dd hh:mm:ss");
	QString		getModule(int chID);
	QString		getDevType(long devtype);
	QString		getDevErrStr(long lResult);
	long		ProcessEvent(PBRI_EVENT pEvent);
	static BRIINT32	WINAPI ProcEventCallback(BRIINT16 uChannelID,BRIUINT32 dwUserData,BRIINT32	lType,BRIINT32 lHandle,BRIINT32 lResult,BRIINT32 lParam,BRIPCHAR8 pData,BRIPCHAR8 pDataEx);

private:

	// 通话类型 1来电，2 去电
	int								m_telType;

	// 录音文件目录
	QString							m_audioDir;

	// 工单查询URL
	QString							m_queryUrl;

	// 来电号码
	QString							m_telnum;

	// 设备序列号
	BRIINT32						m_devnum;

	// 当前通道
	int								m_nChannelID;

	// 录音文件名称
	QString							m_audioName;

	// 录音文件句柄
	long							m_lRecFileHandle;
	QTimer							m_hartBeatTimer;
	Widget							m_popuWin;
	QString							m_title;
	QTextEdit*						m_msg;
	SpWebView						m_webView;

	QSystemTrayIcon *				m_tray;		//托盘图标  
	QMenu *							m_tryMenu;	//托盘菜单  
	QAction *						m_reset;	//菜单实现功能：恢复窗口  
	QAction *						m_quit;		//菜单实现功能：退出程序  
	QAction*						m_setting;	// 设置
	MainController					m_mainControler;
};

#endif // MAINWINDOW_H
