#include "factorydlg.h"

FactoryDlg::FactoryDlg(QWidget *parent)
	: QDialog(parent)
{
	setWindowIcon(QIcon(":images/tray.png"));
	setWindowTitle("添加授权厂家");
	setMinimumWidth(450);
	QVBoxLayout *m_oLayout = new QVBoxLayout;

	QHBoxLayout *m_oFactoryName = new QHBoxLayout;
	QLabel *m_oFactoryTip = new QLabel(QString::fromLocal8Bit("厂  家:"));
	m_oFactoryName->addWidget(m_oFactoryTip,0,Qt::AlignLeft);
	m_pComboBox = new QComboBox;
	m_pComboBox->addItem(QString::fromLocal8Bit("格力"),GREE);
	m_pComboBox->addItem(QString::fromLocal8Bit("TCL"),TCL);
	m_pComboBox->addItem(QString::fromLocal8Bit("美的"),Midea);
	m_pComboBox->addItem(QString::fromLocal8Bit("海尔"),Haier);
	m_pComboBox->addItem(QString::fromLocal8Bit("海信"),Hisense);
	m_pComboBox->addItem(QString::fromLocal8Bit("惠而浦"),Whirlpool);
	m_pComboBox->addItem(QString::fromLocal8Bit("美菱"),MeiLing);
	m_pComboBox->addItem(QString::fromLocal8Bit("奥克斯"),Aux);
	m_pComboBox->addItem(QString::fromLocal8Bit("（老版）海尔"),Old_Haier);
	m_pComboBox->addItem(QString::fromLocal8Bit("苏宁"),Suning);
	m_pComboBox->addItem(QString::fromLocal8Bit("国美"),GoMe);
	m_pComboBox->addItem(QString::fromLocal8Bit("京东"),JD);

	m_pComboBox->setItemText(0,QString::fromLocal8Bit("格力"));
	m_pComboBox->setItemText(1,QString::fromLocal8Bit("TCL"));
	m_pComboBox->setItemText(2,QString::fromLocal8Bit("美的"));
	m_pComboBox->setItemText(3,QString::fromLocal8Bit("海尔"));
	m_pComboBox->setItemText(4,QString::fromLocal8Bit("海信"));
	m_pComboBox->setItemText(5,QString::fromLocal8Bit("惠而浦"));
	m_pComboBox->setItemText(6,QString::fromLocal8Bit("美菱"));
	m_pComboBox->setItemText(7,QString::fromLocal8Bit("奥克斯"));
	m_pComboBox->setItemText(8,QString::fromLocal8Bit("（老版）海尔"));
	m_pComboBox->setItemText(9,QString::fromLocal8Bit("苏宁"));
	m_pComboBox->setItemText(10,QString::fromLocal8Bit("国美"));
	m_pComboBox->setItemText(11,QString::fromLocal8Bit("京东"));

	m_oFactoryName->addWidget(m_pComboBox,1,Qt::AlignLeft);

	QHBoxLayout *m_oUsernamePanel = new QHBoxLayout;
	QLabel *m_oUsernameTip = new QLabel(QString::fromLocal8Bit("用户名:"));
	m_oUsernamePanel->addWidget(m_oUsernameTip);
	m_pUsername = new QLineEdit;
	m_pUsername->setPlaceholderText(QString::fromLocal8Bit("请输入用户名"));
	m_oUsernamePanel->setStretchFactor(m_pUsername,1);
	m_oUsernamePanel->addWidget(m_pUsername);
	
	QHBoxLayout *m_oPasswordPanel = new QHBoxLayout;
	QLabel *m_oPasswordTip = new QLabel(QString::fromLocal8Bit("密  码:"));
	m_oPasswordPanel->addWidget(m_oPasswordTip);
	m_pPassword = new QLineEdit;
	m_pPassword->setPlaceholderText(QString::fromLocal8Bit("请输入密码"));
	m_oPasswordPanel->setStretchFactor(m_pPassword,1);
	m_oPasswordPanel->addWidget(m_pPassword);

	QHBoxLayout *m_oUrlPanel = new QHBoxLayout;
	QLabel *m_oUrlTip = new QLabel(QString::fromLocal8Bit("U R L :"));
	m_oUrlPanel->addWidget(m_oUrlTip);
	m_pUrl = new QLineEdit;
	m_pUrl->setPlaceholderText(QString::fromLocal8Bit("请输入地址"));
	m_oUrlPanel->addWidget(m_pUrl);

	QHBoxLayout *m_oControllPanel = new QHBoxLayout;
	m_pConfirm = new QPushButton;
	m_pConfirm->setFixedWidth(100);
	if(m_vendors.id == 0) {
		m_pConfirm->setText(QString::fromLocal8Bit("确定"));
	} else {
		m_pConfirm->setText(QString::fromLocal8Bit("修改"));
	}
	
	m_oControllPanel->addWidget(m_pConfirm);
	m_pCancel = new QPushButton;
	m_pCancel->setFixedWidth(100);
	m_pCancel->setText(QString::fromLocal8Bit("取消"));
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
		factoryName = QString::fromLocal8Bit("格力");
		m_vendors.vendorFactory = "gree";
		break;
	case TCL:
		factoryName = QString::fromLocal8Bit("TCL");
		m_vendors.vendorFactory = "tcl";
		break;
	case Aux:
		factoryName = QString::fromLocal8Bit("奥克斯");
		m_vendors.vendorFactory = "aux";
		break;
	case GoMe:
		factoryName = QString::fromLocal8Bit("国美");
		m_vendors.vendorFactory = "gome";
		break;
	case Haier:
		factoryName = QString::fromLocal8Bit("海尔");
		m_vendors.vendorFactory = "haier2";
		break;
	case Hisense:
		factoryName = QString::fromLocal8Bit("海信");
		m_vendors.vendorFactory = "hisense";
		break;
	case JD:
		factoryName = QString::fromLocal8Bit("京东");
		m_vendors.vendorFactory = "jd";
		break;
	case MeiLing:
		factoryName = QString::fromLocal8Bit("美菱");
		m_vendors.vendorFactory = "meling";
		break;
	case Midea:
		factoryName = QString::fromLocal8Bit("美的");
		m_vendors.vendorFactory = "midea";
		break;
	case Old_Haier:
		factoryName = QString::fromLocal8Bit("（老版）海尔");
		m_vendors.vendorFactory = "haier";
		break;
	case Suning:
		factoryName = QString::fromLocal8Bit("苏宁");
		m_vendors.vendorFactory = "suning";
		break;
	case Whirlpool:
		factoryName = QString::fromLocal8Bit("惠而浦");
		m_vendors.vendorFactory = "whirlpool";
		break;
	}
	if(factoryName.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("请选择厂家"));
		return;
	}
	QString username = m_pUsername->text();
	if(username.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("用户名不能为空"));
		return;
	}
	QString password = m_pPassword->text();
	if(password.isEmpty()) {
		QMessageBox::information(this,QString::fromLocal8Bit("错误"),QString::fromLocal8Bit("密码不能为空"));
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
	setWindowTitle("修改授权厂家");
	this->m_vendors = vendors;
	if(m_vendors.vendorFactory == "格力") {
		 m_pComboBox->setCurrentIndex(0);
	}
	if(m_vendors.vendorName == "TCL") {
		m_pComboBox->setCurrentIndex(1);
	}
	if(m_vendors.vendorName == "美的") {
		m_pComboBox->setCurrentIndex(2);
	}
	if(m_vendors.vendorName == "海尔") {
		m_pComboBox->setCurrentIndex(3);
	}
	if(m_vendors.vendorName == "海信") {
		m_pComboBox->setCurrentIndex(4);
	}
	if(m_vendors.vendorName == "惠而浦") {
		m_pComboBox->setCurrentIndex(5);
	}
	if(m_vendors.vendorName == "美菱") {
		m_pComboBox->setCurrentIndex(6);
	}
	if(m_vendors.vendorName == "奥克斯") {
		m_pComboBox->setCurrentIndex(7);
	}
	if(m_vendors.vendorName == "（老版）海尔") {
		m_pComboBox->setCurrentIndex(8);
	}
	if(m_vendors.vendorName == "苏宁") {
		m_pComboBox->setCurrentIndex(9);
	}
	if(m_vendors.vendorName == "国美") {
		m_pComboBox->setCurrentIndex(10);
	}
	if(m_vendors.vendorName == "京东") {
		m_pComboBox->setCurrentIndex(11);
	}


	m_pUsername->setText(m_vendors.vendorLoginName);
	m_pPassword->setText(m_vendors.vendorPassword);
	m_pUrl->setText(m_vendors.vendorUrl);
}
