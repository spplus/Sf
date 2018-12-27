#ifndef MAINWDG_H
#define MAINWDG_H
#include <QWidget>
#include <QTableWidget>
#include <QString>
#include <QTimer>
#include <QList>
#include <QMutableListIterator>

#include "common.h"
#include "qhttp/QhttpNetwork.h"
#include "jsoncpp/json.h"
#include "factorylogin.h"
#include "factorydb.h"
#include "factorydlg.h"
#include "loginhelper.h"

class MainWdg : public QWidget
{
	Q_OBJECT

public:
	MainWdg(QWidget *parent = nullptr);
	~MainWdg();
	void						setVendorList(QList<Vendors*>);
	void						refreshVendorList();

	
public slots:
	void						loginResp(Json::Value&);
	void						onLogin();
	void						loging(string, string);
	void						sesstionChecker();
	void						contextMenuEvent(const QPoint &);
	void						onAddButtonRelease();
	void						onData(Vendors);
	void						postVender(Vendors);
	void						factoryReplyData(QByteArray);
	void						onEditEvent();
	void						onDeleteEvent();
	void						onLoginBack(string, string, int);
	void						onReLoginButtonClick();

private:
	void						initView();
	void						initConnect();
	void						checkLogin(Vendors*);
	void						parserSession(Json::Value&);
	void						sendRmSessionTimeout(QString);
	void						sendSessionChecker(Vendors *);
	void						deleteVendor(Vendors);
	void						addReLoginButton(int row, int col);
	int							getVendorInfoById(QString,Vendors *);
	void						insertIntoTable(Vendors* vendor, int row);
	void						insertVendorInfo(Vendors* vendor);
	bool						isLogin(Vendors vendor);
	void						updateVendorInfo(Vendors* vendor);
	void						removeFromLogined(Vendors vendor);
	void						deleteVendorInfo(Vendors* vendor);
	int							getVendorIndex(string, string, Vendors *);

	// 操作类型 1：添加，2 修改
	int								m_opModel;	
	QTableWidget*					m_table;
	QList<Vendors *>				m_vendorList;
	FactoryLogin					m_flogin;
	QTimer*							m_sesstionChecker;
	QList<Vendors *>				m_loginedFactory;
	FactoryDB*						m_factorydb;
	QPushButton*					m_pAddButton;
	const QPoint*					m_pPoint;
	QMenu*							m_pMenu;
	QAction*						m_pEditAction;
	QAction*						m_pDeleteAction;
	FactoryDlg*						m_pFactoryDlg;
	Vendors							m_pVendors;
	QhttpNetwork*					m_pHttpNetwork;
	LoginHelper*					m_pLoginHelper;
	int								m_currentRow;
};

#endif // MAINWDG_H
