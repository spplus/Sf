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

	//��д����ر��¼����رջص���ҳ

	void		closeEvent(QCloseEvent *event);
	void		setVendorData(QList<Vendors*> vendorList);
public slots:

	void		uploadLog();
	void		sysExit();

	// ���ݷ���
	void		replyData(QByteArray data);

	//������ͼ������Ĳۣ�������ʵ�ֵ���ͼ��ָ����ڹ��� 
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
	QSystemTrayIcon *				m_tray;		//����ͼ��  
	QMenu *							m_tryMenu;	//���̲˵�  
	QAction *						m_reset;	//�˵�ʵ�ֹ��ܣ��ָ�����  
	QAction *						m_quit;		//�˵�ʵ�ֹ��ܣ��˳�����  
	QList<Vendors*>					m_vendorList;
};

#endif // MAINWINDOW_H
