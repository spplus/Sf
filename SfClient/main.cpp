#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QCoreApplication>
#include <QPlastiqueStyle>
#include "mainwindow.h"
#include "userlogindlg.h"
#include "gocontroller.h"
#include "configer.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	QApplication::addLibraryPath("./plugins");

	// 设置程序版本号
	QCoreApplication::setApplicationVersion("1.0.2");

#ifdef WIN32
	// 设置编码
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");

	QTextCodec::setCodecForTr(codec);

	QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());

#else
	// 设置编码
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif

	QString appDirPath = QApplication::applicationDirPath();
	
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

	QFile qss(QCoreApplication::applicationDirPath()+"/style.qss");
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
		dlg.doLogin(usr,pwd);
		if (dlg.isLogin())
		{
			goto run;
		}

	}

	
	int isok = dlg.exec();
	if (isok)
	{
		goto run;

		//// 启动go
		//GoController::instance()->goRun();

		//win.setVendorData(dlg.m_vendorList);
		//win.initList();
		//win.show();
		
	}
	else
	{
		goto go;
	}

go:
	exit(0);

run:
	// 启动go
	GoController::instance()->goRun();

	win.setVendorData(dlg.m_vendorList);
	win.initList();
	win.show();

	a.setStyle(new QPlastiqueStyle);

    return a.exec();
}
