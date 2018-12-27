#ifndef _LOGIN_HELPER_H_
#define _LOGIN_HELPER_H_

#include <QObject>
#include <QThread>
#include <QQueue>
#include <QByteArray>
#include <QString>
#include <string>
#include <QDebug>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "common.h"
#include "qhttp/QhttpNetwork.h"
#include "jsoncpp/json.h"

using namespace std;

class LoginHelper:public QThread{
	Q_OBJECT
public:
	LoginHelper(QObject *obj = 0);
	~LoginHelper();

	void							init();
	void							run();
	void							enqueue(Vendors);

signals:
	void							loginResult(string, string, int);

public slots:
	void							replyData(QByteArray);

private:
	void							loginRequest(Vendors);

private:
	QQueue<Vendors>*				m_pVendorQueue;
	bool							isStoped;
	bool							isLogin;
	QhttpNetwork*					m_pHttpClient;
};

#endif
