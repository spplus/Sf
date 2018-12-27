#include "loginhelper.h"
/************************************************************************/
/* 厂家系统登录队列                                                     */
/************************************************************************/

LoginHelper::LoginHelper(QObject *obj) : QThread(obj)
{
	m_pHttpClient = new QhttpNetwork;
	auto queue = new QQueue<Vendors>;
	m_pVendorQueue = queue;

	connect(m_pHttpClient,SIGNAL(response(QByteArray)),this,SLOT(replyData(QByteArray)));

	isStoped =false;
	isLogin =false;
}

LoginHelper::~LoginHelper() {
	isStoped = true;
}

void LoginHelper::init() {
	start();
}

void LoginHelper::run()
{
	while(!isStoped) {
		if(isLogin) {
			QThread::msleep(50);
			// 如果有厂家正在登录,则继续循环
			continue;
		}
		if (m_pVendorQueue->size() == 0) {
			QThread::msleep(50);
			continue;
		}
		Vendors ven = m_pVendorQueue->dequeue();
		loginRequest(ven);
	}
}

void LoginHelper::enqueue(Vendors ven)
{
	m_pVendorQueue->enqueue(ven);
}

/**
 * 厂家账号登录请求
 */
void LoginHelper::loginRequest(Vendors vend)
{
	QString json = QString("{\"user\":\"%1\",\"pwd\":\"%2\",\"factory\":\"%3\",\"mainServerHost\":\"%4\",\"statusReportHost\":\"%5\",\"seqno\":\"%6\"}")
		.arg(vend.vendorLoginName)
		.arg(vend.vendorPassword)
		.arg(vend.vendorFactory)
		.arg(URL_MAIN_SERVER)
		.arg(URL_REPT)
		.arg("1");
	QByteArray req;
	req.append(json.toUtf8());
	auto *manager = new QNetworkAccessManager();
	QNetworkRequest request = QNetworkRequest(QUrl(URL_FACTORY_LONGIN));
	request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json; charset=UTF-8");
	QNetworkReply *reply = manager->post(request, req);
	QByteArray responseData;
	QEventLoop eventLoop;
	connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
	eventLoop.exec();       //block until finish
	responseData = reply->readAll();
	replyData(responseData);
	qDebug() << "json:" << json;
	qDebug("向自动登录接口发送内容:%s",json.toStdString().c_str());
}

void LoginHelper::replyData(QByteArray data)
{
	this->isLogin =false;
	QString msg = QString::fromUtf8(data.data());
	qDebug("[MainWindow->replyData] 接收返回: %s",msg.toStdString().c_str());

	Json::Reader reader;
	Json::Value value;

	if(reader.parse(msg.toStdString(),value))
	{
		string success = value["success"].asString();
		string status = value["status"].asString();

		if (status.length()>1)
		{
			return;
		}
		// 过滤非本类型消息
		if (success.length()<=0)
		{
			return;
		}
		qDebug("收到厂家自动登录返回消息:%s",msg.toStdString().c_str());
		//m_vendorList.clear();
		int loginStatus;
		if (success == "true")
		{
			loginStatus = 1;
			qDebug()<<"厂家账号自动登录成功";
		}
		else
		{
			int code = 0;
			if (value["code"] != NULL)
			{
				code = value["code"].asInt();
			}

			loginStatus = code;
			qDebug("厂家账号自动登录失败,错误码:%d",code);
		}

		string user = value["user"].asString();
		string factory = value["factory"].asString();
		emit loginResult(user,factory,loginStatus);
	}
}
