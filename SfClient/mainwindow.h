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

	//��д����ر��¼����رջص���ҳ

	void		closeEvent(QCloseEvent *event);
	void		setVendorData(QList<Vendors*> vendorList);

signals:
	void		finishPlay();
public slots:
	// ��¼��
	void		loging(int row);
	void		uploadLog();
	void		sysExit();
	void		onLogin();
	void		playSound(int id);

	// WD��¼�ӿڷ���
	void		loginResp(Json::Value& jvalue);

	// ���ݷ���
	void		replyData(QByteArray data);

	void		sendHearBeat();

	// sesstion���ڼ��
	void		sesstionChecker();

	// TCP���������ݷ���
	void		recvdata(int msgtype,const char* msg,int msglength);

	//������ͼ������Ĳۣ�������ʵ�ֵ���ͼ��ָ����ڹ��� 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		parserSession(Json::Value & jvalue);
	void		initWidget();
	void		initTray();
	void		sendSessionChecker(Vendors *vender);
	void		parseTcpResponse(const char* msg);
	void		sendRmSessionTimeout(QString user);

	// ����ע����Ϣ
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
	QSystemTrayIcon *				m_tray;		//����ͼ��  
	QMenu *							m_tryMenu;	//���̲˵�  
	QAction *						m_reset;	//�˵�ʵ�ֹ��ܣ��ָ�����  
	QAction *						m_quit;		//�˵�ʵ�ֹ��ܣ��˳�����  
	QTimer							m_heartBeatTimer;
	QTimer							m_sesstionChecker;
	QList<Vendors*>					m_vendorList;
	PlayThread						m_playThread;
	FactoryLogin					m_flogin;
};

#endif // MAINWINDOW_H
