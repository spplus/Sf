#include <QCoreApplication>
#include <QtGui>

#include "httpdownload.h"


HttpDownload::HttpDownload(QString url,QString dir)
{
	m_file = new QFile;
	m_strUrl = url;
	m_netAccessManager = new QNetworkAccessManager(this);
	m_strDir = dir;

	if( !m_strDir.isEmpty() )//文件夹
	{
		QDir directory( m_strDir );

		if( !directory.exists() )//没有此文件夹，则创建
		{
			directory.mkpath( m_strDir );
		}

	}
}

HttpDownload::~HttpDownload()
{
	if (m_file->isOpen())
	{
		m_file->close();
	}
	delete m_file;

	m_file = NULL;

	delete m_netAccessManager;
	m_netAccessManager = NULL;

	delete m_netReply;
	m_netReply = NULL;
}

void HttpDownload::downLoad(QString filename)
{
	m_strFileName = filename;

	QString filePath = m_strDir +"/"+filename;

	if( QFile::exists(filePath) )
	{
		QFile::remove(filePath);
	}

	// 接收下载文件
	m_file->setFileName(filePath); 

	if(!m_file->open(QIODevice::WriteOnly))
	{
		QMessageBox::warning(NULL,"系统提示","打开文件失败"+filePath);
		return;
	}

	// 设置下载路径
	m_urlAdress.setUrl(m_strUrl+"/"+filename);

	m_netReply = m_netAccessManager->get(QNetworkRequest(m_urlAdress));

	//当有新数据到达时就会触发此信号
	connect(m_netReply,SIGNAL(readyRead()),this,SLOT( replyNewDataArrived()));

	//完成数据接收后发送此信号
	connect(m_netReply, SIGNAL(finished()), this,SLOT(replyFinished()) );

	//出现错误时发送此信号;
	connect(m_netReply, SIGNAL(error(QNetworkReply::NetworkError)),this, SIGNAL( replyError(QNetworkReply::NetworkError)) );

	//用来提示文件下载进度
	connect(m_netReply, SIGNAL(downloadProgress(qint64,qint64)), this, SIGNAL(downloadProgress(qint64,qint64) ) );
}

void HttpDownload::replyFinished()
{
	//m_netAccessManager->deleteLater();
	m_netReply->deleteLater();

	m_file->close();
	//m_file->deleteLater();

	// 发送下载成功消息
	emit downloadSuccess(m_strFileName);

}

void HttpDownload::replyNewDataArrived()
{
	if(m_file)
	{
		m_file->write(m_netReply->readAll());
		m_file->flush();
	}
	else
	{
		qDebug("%s",m_netReply->readAll());
	}
	
}

