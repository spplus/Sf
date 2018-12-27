#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QCoreApplication>
#include <QPlastiqueStyle>
#include <QPluginLoader>
#include "mainwindow.h"
#include "userlogindlg.h"
#include "gocontroller.h"
#include "configer.h"
#include <Windows.h>


bool checkOnly();
void customMessageHandler(QtMsgType type, const char *msg);
void mkdir(QString name);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//检查程序是否 已经启动过  
	if(checkOnly()==false) 
	{
		return 0;  
	}
	// 创建日志目录
	mkdir("log");
	
	//先注册自己的MsgHandler    
	qInstallMsgHandler(customMessageHandler);

	QApplication::addLibraryPath("./plugins");
	QString appDirPath = QApplication::applicationDirPath();

	// 设置程序版本号
	QCoreApplication::setApplicationVersion(Configer::instance()->getVersion());

#ifdef WIN32

	// 设置编码
	QTextCodec *codec = QTextCodec::codecForName("gb2312");

	QTextCodec::setCodecForTr(codec);

	//QTextCodec::setCodecForLocale(codec);
	//QTextCodec::setCodecForCStrings(codec);

	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

#else
	// 设置编码
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

	a.setStyle(new QPlastiqueStyle);

	//	汉字的转换器
	QString translatorPath = appDirPath;

	QDir dir(translatorPath);
	QStringList filters;
	filters << "*.qm" ;
	dir.setNameFilters(filters); 
	foreach(QFileInfo fi,dir.entryInfoList())
	{
		QTranslator *translator = new QTranslator(&a);
		if (translator->load(fi.filePath()))
			a.installTranslator(translator);
	}

	QFile qss(appDirPath+"/style.qss");
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();

	// 登录
	UserLogindlg dlg;
	MainWindow win;

	// 判断是否需要登录
	QString usr = Configer::instance()->getUser();
	QString pwd = Configer::instance()->getPwd();

	if (usr.length()>0 && pwd.length()>0)
	{
		// 自动登录
		/*dlg.doLogin(usr,pwd);
		if (dlg.isLogin())
		{
			goto run;
		}*/

		// 显示登录窗口
		dlg.setUserInfo(usr,pwd);
	}

	
	int isok = dlg.exec();
	if (isok)
	{
		goto run;
	}
	else
	{
		goto go;
	}

go:
	exit(0);

run:
	qDebug() << "Start Go Progress";
	// 启动go
	GoController::instance()->goRun(appDirPath);

	win.setVendorData(dlg.m_vendorList);
	win.show();
	//win.close();


    return a.exec();
}



bool checkOnly()  
{  
	//  创建互斥量  
	HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"sfclient" );  
	//  检查错误代码  
	if  (GetLastError()  ==  ERROR_ALREADY_EXISTS)  {  
		//  如果已有互斥量存在则释放句柄并复位互斥量  
		CloseHandle(m_hMutex);  
		m_hMutex  =  NULL;  
		//  程序退出  
		return  false;  
	}  
	else  
		return true;  
}

void mkdir(QString name)
{
	QString Dir = QCoreApplication::applicationDirPath()+"/"+name;
	QDir directory( Dir );

	if( !directory.exists() )//没有此文件夹，则创建
	{
		directory.mkpath( Dir );
	}
}

void customMessageHandler(QtMsgType type, const char *msg)
{
	QDateTime dt;
	QString ctime = dt.currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
	
	QString txt;
	switch (type)
	{
		//调试信息提示
	case QtDebugMsg:
		txt = QString("[%1]Debug: %2").arg(ctime).arg(msg);
		break;

		//一般的warning提示
	case QtWarningMsg:
		txt = QString("[%1]Warning: %2").arg(ctime).arg(msg);
		break;

		//严重错误提示
	case QtCriticalMsg:
		txt = QString("[%1]Critical: %2").arg(ctime).arg(msg);
		break;

		//致命错误提示
	case QtFatalMsg:
		txt = QString("[%1]Fatal: %2").arg(ctime).arg(msg);
		abort();
	}

	
	ctime = dt.currentDateTime().toString("yyyyMMdd");

	QString fname = "sfclient_"+ctime+".txt";
	fname = "log/"+fname;
	QFile outFile(fname);
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
}
