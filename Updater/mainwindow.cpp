#include "mainwindow.h"
#include <string>
#include <QPushButton>
#include <QFileDialog>
#include <qfile.h>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QSettings>
#include <QProcess>

using namespace std;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	m_workDir = QCoreApplication::applicationDirPath()+"/";
	m_tempDir = m_workDir+"/temp";

	
	initWidget();

	int w = 400;
	int h = 200;
	int x = (QApplication::desktop()->width() - w)-20;
	int y = (QApplication::desktop()->height() - h)-40;
	
	setGeometry(QRect(x,y,w,h));
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("自动升级");
	setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

}

MainWindow::~MainWindow()
{

}


void MainWindow::initWidget()
{

	QVBoxLayout* vbox = new QVBoxLayout;
	
	m_info = new QLabel;
	m_bar = new QProgressBar;
	m_bar->setMinimum(0);
	vbox->addStretch();
	vbox->addWidget(m_info);
	vbox->addSpacing(3);
	vbox->addWidget(m_bar);
	vbox->addStretch();

	QWidget *centralWidget = new QWidget;
	centralWidget->setLayout(vbox);
	setCentralWidget(centralWidget);
}


void MainWindow::doUpdate(QString url,QString appname,QString files)
{
	m_url = url;
	m_appName = appname;
	QStringList filelist = files.split(",");
	for (int i = 0;i<filelist.size();i++)
	{
		m_totalList.push_back(filelist.at(i));
	}

	m_httpDown = new HttpDownload(url,m_tempDir);
	connect(m_httpDown,SIGNAL(downloadProgress(qint64 , qint64 )),this,SLOT(updateProgress(qint64 , qint64 )));
	connect(m_httpDown,SIGNAL(replyError(QNetworkReply::NetworkError)),this,SLOT(replyError(QNetworkReply::NetworkError )));
	connect(m_httpDown,SIGNAL(downloadSuccess(QString )),this,SLOT(downloadSuccess(QString )));

	/*m_totalList.push_back("conf.ini");
	m_totalList.push_back("SfClient.exe");
	m_totalList.push_back("style.qss");
	m_totalList.push_back("woodpecker_windows_386.exe");*/
	
	m_leftList = m_totalList;

	execUpdate();
	
}

void MainWindow::execUpdate()
{
	int idx = m_totalList.size()-m_leftList.size();

	QString filename = m_totalList.at(idx);
	QString info = QString("[%1/%2]正在更新文件--->%3 ... ").arg(idx+1).arg(m_totalList.size()).arg(filename);

	// 调用下载接口，下载文件
	m_info->setText(info);

	m_httpDown->downLoad(filename);
}


void MainWindow::afterUpdate()
{
	int flag = 0;

	// 备份原来文件
	for (int i = 0;i<m_totalList.size();i++)
	{
		QString fname = m_totalList.at(i);
		QString oldName = m_tempDir+"/"+fname;
		QString newName = m_workDir+fname;
		QString backName = m_workDir+fname+".back";

		// 备份原文件
		if (QFile::exists(backName))
		{
			QFile::remove(backName);
		}
		QFile::rename(newName,backName);
		

		if(!QFile::rename(oldName,newName))
		{
			flag = 1;
			QMessageBox::warning(this,"系统提示","移动文件失败:"+oldName);
		}
		else
		{
			QFile::remove(oldName);
		}
		
	}
	// 如果发生错误，则恢复备份文件
	if (flag == 1)
	{
		rollbackUpdate();
	}
	else
	{
		// 删除备份文件
		for (int i = 0;i<m_totalList.size();i++)
		{
			QString fname = m_totalList.at(i);
			QString backName = m_workDir+fname+".back";
			QFile::remove(backName);
		}
	}

	// 删除temp目录
	QDir directory( m_tempDir );
	if (directory.exists())
	{
		directory.rmdir(m_tempDir);
	}

}

void MainWindow::rollbackUpdate()
{
	for (int i = 0;i<m_totalList.size();i++)
	{
		QString fname = m_totalList.at(i);
		QString newName = m_workDir+fname;
		QString backName = m_workDir+fname+".back";
		if (QFile::exists(newName))
		{
			QFile::remove(newName);
		}
		QFile::rename(backName,newName);
	}

	QMessageBox::warning(this,"系统提示","升级失败");
	exit(0);
}

void MainWindow::updateProgress( qint64 bytesReceived, qint64 bytesTotal )
{
	m_bar->setMaximum(bytesTotal);
	m_bar->setValue(bytesReceived);
}


void MainWindow::downloadSuccess(QString filename)
{

	// 更新已下载
	m_bar->reset();
	
	m_leftList.removeOne(filename);


	if (m_leftList.size() == 0)
	{
		m_info->setText("更新完成");
		m_bar->hide();

		// 把文件从temp目录移动到工作目录
		afterUpdate();

		// 启动主程序
		startMain();

	}
	else
	{
		// 继续下载
		execUpdate();
	}
}

void MainWindow::startMain()
{
	QProcess pro;
	pro.start(m_appName);

	// 退出自己
	exit(0);
}

void MainWindow::replyError(QNetworkReply::NetworkError err)
{
	QMessageBox::warning(this,"系统提示","升级发生错误");
	exit(0);
}


