#ifndef __CONFIGER_H__
#define __CONFIGER_H__

#include <QSettings>

class Configer
{
public:
	static Configer* instance();
	~Configer();
	QString		getUrl();
	QString		getUser();
	QString		getPwd();
	void		setUser(QString user);
	void		setPwd(QString pwd);
private:
	Configer();
private:
	QString					m_url;
	QString					m_user;
	QString					m_pwd;
	QSettings*				m_setting;
	static  Configer*		m_inst;
};
#endif