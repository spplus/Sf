#include "QhttpNetwork.h"

QhttpNetwork* QhttpNetwork::m_inst = NULL;

QhttpNetwork* QhttpNetwork::instance()
{
	if (m_inst == NULL)
	{
		m_inst = new QhttpNetwork();
	}
	return m_inst;
}

QhttpNetwork::QhttpNetwork(QObject *parent) :
QObject(parent)
{
	m_manager = new QNetworkAccessManager(this);
	connect(m_manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));
}

void QhttpNetwork::replyFinished(QNetworkReply *reply)
{
	if(reply && reply->error() == QNetworkReply::NoError) {
		QByteArray data = reply->readAll();
		emit this->response(data);
		
	} else {
		qDebug("%d:%s",reply->error(),reply->errorString());
		emit this->error((int)reply->error());
	}
	reply->close();
}

void QhttpNetwork::post(QString strUrl,QByteArray& data)
{
	QNetworkRequest request;
	request.setUrl(QUrl(strUrl));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json; charset=UTF-8");

	m_manager->post(request,data);
}

void QhttpNetwork::get(QString strUrl)
{
	QNetworkRequest request;
	request.setUrl(QUrl(strUrl));
	m_manager->get(request);
}