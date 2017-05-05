#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QCoreApplication>
#include <QPlastiqueStyle>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


	QApplication::addLibraryPath("./plugins");

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

	qDebug("启动参数个数：%d",argc);
	
	for (int i = 0;i<argc;i++)
	{
		//QMessageBox::information(NULL,"",argv[i]);
		qDebug("参数%d是:%s",i,argv[i]);
	}
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

	
	MainWindow win;
	win.show();
	win.doUpdate(argv[2],argv[1],argv[3]);

	a.setStyle(new QPlastiqueStyle);

    return a.exec();
}
