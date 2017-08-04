#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QCoreApplication>
#include <QPlastiqueStyle>
#include "mainwindow.h"
#include <Windows.h>


bool checkOnly();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//检查程序是否 已经启动过  
	if(checkOnly()==false) 
	{
		return 0;  
	}
	QApplication::addLibraryPath("./plugins");

	// 设置程序版本号
	QCoreApplication::setApplicationVersion("1.0.0");


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

	a.setStyle(new QPlastiqueStyle);
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

	QFile qss(appDirPath+"/style.qss");
	qss.open(QFile::ReadOnly);
	a.setStyleSheet(qss.readAll());
	qss.close();

	// 登录
	MainWindow win;
	//win.show();
	win.showMinimized();
	win.close();
    return a.exec();
}


bool checkOnly()  
{  
	//  创建互斥量  
	HANDLE m_hMutex  =  CreateMutex(NULL, FALSE,  L"telhelper" );  
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