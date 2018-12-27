#include "factorydlg.h"

FactoryDlg::FactoryDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("�����Ȩ����");
	setMinimumWidth(450);
	QVBoxLayout *m_oLayout = new QVBoxLayout;

	QHBoxLayout *m_oFactoryName = new QHBoxLayout;
	QLabel *m_oFactoryTip = new QLabel(QString::fromLocal8Bit("��  ��:"));
	m_oFactoryName->addWidget(m_oFactoryTip,0,Qt::AlignLeft);
	m_pComboBox = new QComboBox;
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),GREE);
	m_pComboBox->addItem(QString::fromLocal8Bit("TCL"),TCL);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),Midea);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),Haier);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),Hisense);
	m_pComboBox->addItem(QString::fromLocal8Bit("�ݶ���"),Whirlpool);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),MeiLing);
	m_pComboBox->addItem(QString::fromLocal8Bit("�¿�˹"),Aux);
	m_pComboBox->addItem(QString::fromLocal8Bit("���ϰ棩����"),Old_Haier);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),Suning);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),GoMe);
	m_pComboBox->addItem(QString::fromLocal8Bit("����"),JD);

	m_pComboBox->setItemText(0,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(1,QString::fromLocal8Bit("TCL"));
	m_pComboBox->setItemText(2,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(3,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(4,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(5,QString::fromLocal8Bit("�ݶ���"));
	m_pComboBox->setItemText(6,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(7,QString::fromLocal8Bit("�¿�˹"));
	m_pComboBox->setItemText(8,QString::fromLocal8Bit("���ϰ棩����"));
	m_pComboBox->setItemText(9,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(10,QString::fromLocal8Bit("����"));
	m_pComboBox->setItemText(11,QString::fromLocal8Bit("����"));

	m_oFactoryName->addWidget(m_pComboBox,1,Qt::AlignLeft);

	QHBoxLayout *m_oUsernamePanel = new QHBoxLayout;
	QLabel *m_oUsernameTip = new QLabel(QString::fromLocal8Bit("�û���:"));
	m_oUsernamePanel->addWidget(m_oUsernameTip);
	m_pUsername = new QLineEdit;
	m_pUsername->setPlaceholderText(QString::fromLocal8Bit("�������û���"));
	m_oUsernamePanel->setStretchFactor(m_pUsername,1);
	m_oUsernamePanel->addWidget(m_pUsername);
	
	QHBoxLayout *m_oPasswordPanel = new QHBoxLayout;
	QLabel *m_oPasswordTip = new QLabel(QString::fromLocal8Bit("��  ��:"));
	m_oPasswordPanel->addWidget(m_oPasswordTip);
	m_pPassword = new QLineEdit;
	m_pPassword->setPlaceholderText(QString::fromLocal8Bit("����������"));
	m_oPasswordPanel->setStretchFactor(m_pPassword,1);
	m_oPasswordPanel->addWidget(m_pPassword);

	QHBoxLayout *m_oUrlPanel = new QHBoxLayout;
	QLabel *m_oUrlTip = new QLabel(QString::fromLocal8Bit("U R L :"));
	m_oUrlPanel->addWidget(m_oUrlTip);
	m_pUrl = new QLineEdit;
	m_pUrl->setPlaceholderText(QString::fromLocal8Bit("�������ַ"));
	m_oUrlPanel->addWidget(m_pUrl);

	QHBoxLayout *m_oControllPanel = new QHBoxLayout;
	m_pConfirm = new QPushButton;
	m_pConfirm->setFixedWidth(100);
	if(m_vendors.id == 0) {
		m_pConfirm->setText(QString::fromLocal8Bit("ȷ��"));
	} else {
		m_pConfirm->setText(QString::fromLocal8Bit("�޸�"));
	}
	
	m_oControllPanel->addWidget(m_pConfirm);
	m_pCancel = new QPushButton;
	m_pCancel->setFixedWidth(100);
	m_pCancel->setText(QString::fromLocal8Bit("ȡ��"));
	m_oControllPanel->addWidget(m_pCancel);
	
	m_oLayout->addLayout(m_oFactoryName);
	m_oLayout->addSpacing(8);
	m_oLayout->addLayout(m_oUsernamePanel);
	m_oLayout->addSpacing(8);
	m_oLayout->addLayout(m_oPasswordPanel);
	m_oLayout->addSpacing(16);
	m_oLayout->addLayout(m_oControllPanel);

	setLayout(m_oLayout);

	connect(m_pConfirm,SIGNAL(released()),this,SLOT(onConfirm()));
	connect(m_pCancel,SIGNAL(released()),this,SLOT(onCancel()));
}

FactoryDlg::~FactoryDlg()
{

}

void FactoryDlg::onConfirm() {
	auto factory = (Factory)(m_pComboBox->currentIndex());
	QString factoryName;
	switch(factory) {
	case GREE:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "gree";
		break;
	case TCL:
		factoryName = QString::fromLocal8Bit("TCL");
		m_vendors.vendorFactory = "tcl";
		break;
	case Aux:
		factoryName = QString::fromLocal8Bit("�¿�˹");
		m_vendors.vendorFactory = "aux";
		break;
	case GoMe:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "gome";
		break;
	case Haier:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "haier2";
		break;
	case Hisense:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "hisense";
		break;
	case JD:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "jd";
		break;
	case MeiLing:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "meling";
		break;
	case Midea:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "midea";
		break;
	case Old_Haier:
		factoryName = QString::fromLocal8Bit("���ϰ棩����");
		m_vendors.vendorFactory = "haier";
		break;
	case Suning:
		factoryName = QString::fromLocal8Bit("����");
		m_vendors.vendorFactory = "suning";
		break;
	case Whirlpool:
		factoryName = QString::fromLocal8Bit("�ݶ���");
		m_vendors.vendorFactory = "whirlpool";
		break;
	}
	if(factoryName.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("��ѡ�񳧼�"));
		return;
	}
	QString username = m_pUsername->text();
	if(username.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("�û�������Ϊ��"));
		return;
	}
	QString password = m_pPassword->text();
	if(password.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("����"),QString::fromLocal8Bit("���벻��Ϊ��"));
		return;
	}
	m_vendors.sfAccount = Configer::instance()->getUser();
	m_vendors.vendorName = factoryName;
	m_vendors.vendorLoginName = username;
	m_vendors.vendorPassword = password;
	emit onData(m_vendors);
	this->accept();
}

void FactoryDlg::onCancel() {
	this->reject();
}

void FactoryDlg::setData(Vendors vendors) {
	setWindowTitle("�޸���Ȩ����");
	this->m_vendors = vendors;
	if(m_vendors.vendorFactory == "����") {
		 m_pComboBox->setCurrentIndex(0);
	}
	if(m_vendors.vendorName == "TCL") {
		m_pComboBox->setCurrentIndex(1);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(2);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(3);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(4);
	}
	if(m_vendors.vendorName == "�ݶ���") {
		m_pComboBox->setCurrentIndex(5);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(6);
	}
	if(m_vendors.vendorName == "�¿�˹") {
		m_pComboBox->setCurrentIndex(7);
	}
	if(m_vendors.vendorName == "���ϰ棩����") {
		m_pComboBox->setCurrentIndex(8);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(9);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(10);
	}
	if(m_vendors.vendorName == "����") {
		m_pComboBox->setCurrentIndex(11);
	}


	m_pUsername->setText(m_vendors.vendorLoginName);
	m_pPassword->setText(m_vendors.vendorPassword);
	m_pUrl->setText(m_vendors.vendorUrl);
}
