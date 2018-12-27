#include "loginhelper.h"
/************************************************************************/
/* ����ϵͳ��¼����                                                     */
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
			// ����г������ڵ�¼,�����ѭ��
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
 * �����˺ŵ�¼����
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
	qDebug("���Զ���¼�ӿڷ�������:%s",json.toStdString().c_str());
}

void LoginHelper::replyData(QByteArray data)
{
	this->isLogin =false;
	QString msg = QString::fromUtf8(data.data());
	qDebug("[MainWindow->replyData] ���շ���: %s",msg.toStdString().c_str());

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
		// ���˷Ǳ�������Ϣ
		if (success.length()<=0)
		{
			return;
		}
		qDebug("�յ������Զ���¼������Ϣ:%s",msg.toStdString().c_str());
		//m_vendorList.clear();
		int loginStatus;
		if (success == "true")
		{
			loginStatus = 1;
			qDebug()<<"�����˺��Զ���¼�ɹ�";
		}
		else
		{
			int code = 0;
			if (value["code"] != NULL)
			{
				code = value["code"].asInt();
			}

			loginStatus = code;
			qDebug("�����˺��Զ���¼ʧ��,������:%d",code);
		}

		string user = value["user"].asString();
		string factory = value["factory"].asString();
		emit loginResult(user,factory,loginStatus);
	}
}
