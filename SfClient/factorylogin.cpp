#include <QNetworkRequest>
#include <QNetworkReply>
#include <QSslConfiguration>
#include "factorylogin.h"

FactoryLogin::FactoryLogin(QWidget* parent):QDialog(parent)
{
	
	QVBoxLayout*	mbox = new QVBoxLayout;
	QHBoxLayout*	hbox = new QHBoxLayout;
	QHBoxLayout*	h2box = new QHBoxLayout;
	QLineEdit*		capt = new QLineEdit;
	QPushButton* loginBtn = new QPushButton("��½");
	m_captchaImg = new QLabel;
	hbox->addWidget(capt);
	hbox->addWidget(m_captchaImg);
	h2box->addStretch();
	h2box->addWidget(loginBtn);
	h2box->addStretch();
	mbox->addLayout(hbox);
	mbox->addLayout(h2box);
	setLayout(mbox);
	setWindowTitle("��½����");
	connect(&m_networkManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));
	loadImg();
}

void FactoryLogin::showDlg()
{

}
void FactoryLogin::loadImg()
{
	QNetworkRequest request;

	// ����https����ǰ׼������;
	//QSslConfiguration conf = request.sslConfiguration();
	/*QSslConfiguration conf = request.sslConfiguration();
	conf.setPeerVerifyMode(QSslSocket::VerifyNone);
	conf.setProtocol(QSsl::TlsV1SslV3);
	request.setSslConfiguration(conf);
	*/

	request.setUrl(QUrl("http://avatar.csdn.net/6/9/A/1_u011012932.jpg"));
	
	m_networkManager.get(request);

}

void FactoryLogin::replyFinished(QNetworkReply *reply)
{
	
	// ��ȡ��Ӧ״̬�룬200��ʾ����
	// QVariant nCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray bytes = reply->readAll();
		QPixmap pixmap;
		pixmap.loadFromData(bytes);
		m_captchaImg->setPixmap(pixmap);

		// ���浽����
		QFile file("E:/head.jpg");
		if (file.open(QIODevice::Append))
			file.write(bytes);

		file.close();
		this->exec();
	}
	else
	{
		// ������-��ʾ������Ϣ������ʾ��һ�λ����ͼƬ���ͼ��
	}
}