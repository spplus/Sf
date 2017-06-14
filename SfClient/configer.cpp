#include "configer.h"
#include <QCoreApplication>
Configer* Configer::m_inst = NULL;

Configer::Configer()
{
	m_setting = new QSettings(QCoreApplication::applicationDirPath()+"/conf.ini", QSettings::IniFormat);
	m_url= m_setting->value("SF/url").toString();
	m_user = m_setting->value("SF/usr").toString();
	m_pwd = m_setting->value("SF/pwd").toString();
	m_url = "http://sifangerp.com/clsorder/main/redirect/assistantLogin";

}

Configer::~Configer()
{
	delete m_setting;
	m_setting = NULL;
}
Configer* Configer::instance()
{
	if (m_inst == NULL)
	{
		m_inst = new Configer;
	}
	return m_inst;
}

QString Configer::getPwd()
{
	return m_pwd;
}

QString Configer::getUrl()
{
	return m_url;
}

QString Configer::getUser()
{
	return m_user;
}

void Configer::setPwd(QString pwd)
{
	m_setting->setValue("/SF/pwd",pwd);
}

void Configer::setUser(QString user)
{
	m_setting->setValue("/SF/usr",user);
}

void Configer::setSiteId(QString siteid)
{
	m_setting->setValue("/SF/site",siteid);
}

QString Configer::getSiteId()
{
	return m_setting->value("SF/site").toString();
}

QString Configer::getValue(QString key)
{
	return m_setting->value(key).toString();
}

void Configer::setValue(QString key,QString val)
{
	m_setting->setValue(key,val);
}