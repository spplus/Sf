#ifndef __HTTPDOWNLOAD_H__
#define __HTTPDOWNLOAD_H__
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QFile>
class HttpDownload	:public QObject
{
	Q_OBJECT
public:
	HttpDownload(QString url,QString dir);
	~HttpDownload();

	// 执行下载文件
	void	downLoad(QString filename);

public slots:

	//响应m_netReply有新的数据到达
	void		replyNewDataArrived();

	//响应数据接收完成
	void		replyFinished();

signals:
	void		downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
	void		downloadSuccess(QString filename);
	void		replyError(QNetworkReply::NetworkError err);
private:
	

	//网络地址
	QUrl		m_urlAdress;

	//需要下载的文件名
	QString		m_strFileName;

	QString		m_strUrl;
	
	//文件的存储位置
	QString		m_strDir;
	
	//下载的文件
	QFile *		m_file;



	QNetworkReply *				m_netReply;
	QNetworkAccessManager *		m_netAccessManager;//网络参数
};

#endif