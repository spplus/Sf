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
#include <Phonon/MediaObject>
#include <Phonon/MediaSource>
#include <Phonon/AudioOutput>

#include "common.h"

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
public slots:

	void		uploadLog();
	void		sysExit();

	// ���ݷ���
	void		replyData(QByteArray data);


	// TCP���������ݷ���
	void		recvdata(int msgtype,const char* msg,int msglength);

	//������ͼ������Ĳۣ�������ʵ�ֵ���ͼ��ָ����ڹ��� 
	void		trayIconAction(QSystemTrayIcon::ActivationReason reason);
private:
	void		initWidget();
	void		initTray();
	void		initMedia();

	// ����ע����Ϣ
	void		sendReg();
	void		autoRun(bool bAutoRun = true);
	void		checkLogin(Vendors* vend);
	void		updateLoginState(QString user,int status);
	QToolButton*	tbFactory(QString btnName);
private:

	QLabel*							m_status;
	QString							m_title;
	QTableWidget*					m_table;
	QSystemTrayIcon *				m_tray;		//����ͼ��  
	QMenu *							m_tryMenu;	//���̲˵�  
	QAction *						m_reset;	//�˵�ʵ�ֹ��ܣ��ָ�����  
	QAction *						m_quit;		//�˵�ʵ�ֹ��ܣ��˳�����  
	QList<Vendors*>					m_vendorList;

	Phonon::MediaObject 			m_mediaObject;
	Phonon::AudioOutput				m_audioOutput;
};

#endif // MAINWINDOW_H
