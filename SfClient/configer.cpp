#include "configer.h"
#include <QCoreApplication>
#include <QFile>
#include <QtGui>
Configer* Configer::m_inst = NULL;

Configer::Configer()
{
	
	QString strAppPath = QCoreApplication::applicationDirPath();
	QString csFile = strAppPath + "/conf.ini";
	QString csFileTemp = strAppPath + "/sf.d";
	QString csFileUser = strAppPath + "/us.d";
	m_userSetting = new QSettings(csFileUser, QSettings::IniFormat);

	Encrypt((char*)csFile.toStdString().c_str(),INCODE_PWD,(char*)csFileTemp.toStdString().c_str());
	m_setting = new QSettings(csFileTemp, QSettings::IniFormat);
	

	m_url= m_setting->value("SF/url").toString();
	m_user = m_userSetting->value("SF/usr").toString();
	m_pwd = m_userSetting->value("SF/pwd").toString();

	m_tcpSrv = m_setting->value(ADDR_KEY).toString();
	m_tcpPort = m_setting->value(PORT_KEY).toString().toInt();
	m_mainSrv = m_setting->value(MAIN_SRV_KEY).toString();
	m_version = m_setting->value(VER_KEY).toString();

	QFile tempFile(csFileTemp);
	bool ret = tempFile.remove();
	tempFile.close();
}

Configer::~Configer()
{
	delete m_setting;
	m_setting = NULL;

	delete m_userSetting;
	m_userSetting = NULL;
}
Configer* Configer::instance()
{
	if (m_inst == NULL)
	{
		m_inst = new Configer;
	}
	return m_inst;
}

QString Configer::getMainSvr()
{
	return m_mainSrv;
}
QString Configer::getVersion()
{
	return m_version;
}
QString Configer::getTcpSvr()
{
	return m_tcpSrv;
}

int Configer::getTcpPort()
{
	return m_tcpPort;
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
	m_userSetting->setValue("/SF/pwd",pwd);
}

void Configer::setUser(QString user)
{
	m_userSetting->setValue("/SF/usr",user);
}

void Configer::setSiteId(QString siteid)
{
	m_userSetting->setValue("/SF/site",siteid);
}

QString Configer::getSiteId()
{
	return m_userSetting->value("SF/site").toString();
}

QString Configer::getValue(QString key)
{
	return m_setting->value(key).toString();
}

void Configer::setValue(QString key,QString val)
{
	m_setting->setValue(key,val);
}

void Configer::Encrypt(char *s_file , char *pwd ,char *c_file)
{
	int i=0 ;
	FILE *fp1,*fp2 ;
	register char ch ;
	fp1=fopen(s_file,"rb") ;
	if(fp1==NULL)
	{
		return;
	}
	fp2=fopen(c_file,"wb") ;
	if(fp2==NULL)
	{
		return;
	}
	ch=fgetc(fp1) ;
	while(!feof(fp1))
	{
		ch=ch^*(pwd+i);
		i++ ;
		fputc(ch,fp2);
		ch=fgetc(fp1);
		if(i>9)
			i=0 ;
	}
	fclose(fp1);
	fclose(fp2);
}