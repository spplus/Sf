#ifndef __CONFIGER_H__
#define __CONFIGER_H__

#include <QSettings>

#define		ADDR_KEY		"SF/addr"
#define		PORT_KEY		"SF/port"
#define		MAIN_SRV_KEY	"SF/main_server"
#define		VER_KEY			"SF/version"
#define		INCODE_PWD		"&78ad697$"  

class Configer
{
public:
	static Configer* instance();
	~Configer();
	QString		getUrl();
	QString		getUser();
	QString		getPwd();
	QString		getTcpSvr();
	QString		getMainSvr();
	int			getTcpPort();
	void		setUser(QString user);
	void		setPwd(QString pwd);
	void		setSiteId(QString siteid);
	QString		getSiteId();
	QString		getValue(QString key);
	void		setValue(QString key,QString val);
	
private:
	Configer();

	void		Encrypt(char *s_file , char *pwd ,char *c_file);
private:
	QString					m_url;
	QString					m_user;
	QString					m_pwd;
	QString					m_tcpSrv;
	int						m_tcpPort;
	QString					m_mainSrv;

	QSettings*				m_setting;
	QSettings*				m_userSetting;
	static  Configer*		m_inst;
};
#endif