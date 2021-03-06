#ifndef __QHTTPNETWORK_H__ 
#define __QHTTPNETWORK_H__

#include <QNetworkReply>
#include <QNetworkAccessManager>

class QhttpNetwork : public QObject
{
	Q_OBJECT

public:
	QhttpNetwork(QObject *parent = 0);
	static	QhttpNetwork* instance();
signals:
		
		void response(QByteArray resp);
		void error(int errCode);
public slots:
		void post(QString strUrl,QByteArray& data);
		void get(QString strUrl);
		void replyFinished(QNetworkReply* reply);
private:
	static QhttpNetwork*	m_inst;
	QNetworkAccessManager*	m_manager;
};
#endif