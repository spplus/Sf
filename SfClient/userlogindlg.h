

#ifndef USERLOGINDLG_H
#define USERLOGINDLG_H
#include <QList>
#include <QObject>
#include <QtGui>
#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include "common.h"
#include <qmath.h>

class UserLogindlg : public QDialog
{
	Q_OBJECT

public:
	UserLogindlg();
	~UserLogindlg();

	void	doLogin(QString usr,QString pwd);
	bool	isLogin();
public slots:
	void	closeWin();
	void	login();
	void	loginResp(QByteArray resp);

private:
	void	iniUi();
	bool	versionCheck(QString version);


protected:
	void mousePressEvent(QMouseEvent *event);		//鼠标点击响应事件
	void mouseReleaseEvent(QMouseEvent *event);		//鼠标释放响应事件
	void mouseMoveEvent(QMouseEvent *event);		//鼠标移动响应事件
private:
	bool					m_loginOk;
	QString					m_md5pwd;
	QPoint					move_point;								//移动的距离
	bool					mouse_press;								//按下鼠标左键
	QLineEdit*				m_userAccount;
	QLineEdit*				m_userPassword;
	QPushButton*			m_loginBtn;
public:
	QList<Vendors*>			m_vendorList;
};

#endif // USERLOGINDLG_H
