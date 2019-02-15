#include <QVBoxLayout>
#include <QAbstractItemView>
#include <QStringList>
#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QPalette>
#include <QFont>
#include <Windows.h>
#include <string>
#include <QMessageBox>

#include "mainwdg.h"
#include "titlewidget.h"
#include "factorydb.h"

using namespace std;

MainWdg::MainWdg(QWidget *parent)
	: QWidget(parent),
	m_flogin(this),
	m_vendorList()
{
	qRegisterMetaType<string>("string");
	m_sesstionChecker = new QTimer();
	m_sesstionChecker->setInterval(SF_SESSIONCHER_INTERVAL);
	m_factorydb = new FactoryDB;
	m_pHttpNetwork = new QhttpNetwork;
	m_pLoginHelper = new LoginHelper;
	m_opModel = 1;
	initView();
	initConnect();
	m_currentRow = -1;
	m_pLoginHelper->init();
}

MainWdg::~MainWdg()
{
	if (m_sesstionChecker) {
		m_sesstionChecker->stop();
	}
}

void MainWdg::initView() {
	auto* vbox = new QVBoxLayout;

	m_pAddButton = new QPushButton;
	m_pAddButton->setText(QString::fromLocal8Bit("添加"));
	m_pAddButton->setFixedWidth(100);
	m_pAddButton->setStyleSheet("QPushButton { \
								border:1px solid #CCCCCC;\
								background-color:white;\
								height:24px;\
								border-radius: 5px;\
								}\
								QPushButton::pressed {\
								background-color:#0094FF;\
								border:0px;\
								color: white;\
								}\
								QPushButton::hover {\
								background-color:#0094FF;\
								border:0px;\
								color: white;\
								}\
								");
	auto *mLayout = new QHBoxLayout;
	mLayout->addWidget(m_pAddButton);
	mLayout->addStretch();
	vbox->addLayout(mLayout);

	m_table = new QTableWidget;
	m_table->verticalHeader()->setHidden(true);
	m_table->horizontalHeader()->setClickable(true);
	m_table->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	//m_table->setEditTriggers ( QAbstractItemView::NoEditTriggers );
	m_table->setColumnCount(4);
	QStringList headers;
	headers<<"厂家"<<"账号"<<"状态"<<"操作";
	m_table->setHorizontalHeaderLabels(headers);
	m_table->setFrameShape(QFrame::NoFrame);
	m_table->setContextMenuPolicy(Qt::CustomContextMenu);
	m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
	m_table->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	m_table->setAlternatingRowColors(true);
	m_table->setStyleSheet("QTableWidget{alternate-background-color:#BBFFFF}");

	m_table->horizontalHeader()->setResizeMode(0, QHeaderView::Fixed);
	m_table->horizontalHeader()->setResizeMode(1, QHeaderView::Fixed);
	m_table->horizontalHeader()->setResizeMode(2, QHeaderView::Stretch);
	m_table->horizontalHeader()->setResizeMode(3, QHeaderView::Fixed);

	vbox->addWidget(m_table);

	QLabel *m_pTip = new QLabel;
	m_pTip->setText(QString::fromLocal8Bit("提示：1. TCL需要手动点击登录，输入验证码才可以正常登录。\n      2. 其他账号登录时，提示异常或者账号密码错误。请到(文件->账号维护)中检查您的授权账号和密码。"));
	QPalette tipPalette = m_pTip->palette();
	tipPalette.setColor(QPalette::WindowText,QColor(255,0,0));
	m_pTip->setPalette(tipPalette);
	vbox->addWidget(m_pTip);
	vbox->addSpacing(8);
	setLayout(vbox);
}

void MainWdg::initConnect() {
	// 添加按钮
	connect(m_pAddButton,SIGNAL(released()),this,SLOT(onAddButtonRelease()));
	// QTableWidget 右键点击
	connect(m_table,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(contextMenuEvent(const QPoint&)));
	// 厂家登录队列
	connect(m_pLoginHelper,SIGNAL(loginResult(string,string,int)),this,SLOT(onLoginBack(string,string,int)),Qt::AutoConnection);
	// 厂家账号同步到服务器请求
	connect(m_pHttpNetwork,SIGNAL(response(QByteArray)),this,SLOT(factoryReplyData(QByteArray)));
	connect(&m_flogin,SIGNAL(loginResp(Json::Value&)),this,SLOT(loginResp(Json::Value&)));
	connect(&m_flogin,SIGNAL(loging(string,string)),this,SLOT(loging(string,string)));
	connect(m_sesstionChecker,SIGNAL(timeout()),this,SLOT(sesstionChecker()));
}

void MainWdg::onAddButtonRelease() {
	m_opModel = 1;
	m_pFactoryDlg = new FactoryDlg(this);
	connect(m_pFactoryDlg,SIGNAL(onData(Vendors)),this,SLOT(onData(Vendors)));
	m_pFactoryDlg->show();
}

void MainWdg::onData(Vendors ven) {
	// 发送账号信息到服务器
	postVender(ven);
}

void MainWdg::postVender(Vendors ven) {


	m_pVendors = ven;
	
	QString params = "";
	QString url = "";
	if (m_opModel == 1)
	{
		params = QString("{\"site_id\":\"%1\",\"login_name\":\"%2\",\"password\":\"%3\",\"name\":\"%4\"}")
			.arg(Configer::instance()->getSiteId())
			.arg(ven.vendorLoginName)
			.arg(ven.vendorPassword)
			.arg(ven.vendorFactory)
			.arg(ven.vendorPassword);
		url = URL_ADD_FACTORY;
	}
	else{
		params = QString("{\"id\":\"%1\",\"login_name\":\"%2\",\"password\":\"%3\"}")
			.arg(ven.serverId)
			.arg(ven.vendorLoginName)
			.arg(ven.vendorPassword);
		url = URL_EDIT_FACTORY;
	}		

	qDebug() << "[SettingWdg->postVender] 请求参数: " << params;
	QByteArray rawParam;
	rawParam.append(params.toUtf8());
	m_pHttpNetwork->post(url,rawParam);
}

void MainWdg::contextMenuEvent(const QPoint &pos) {
	m_pPoint = &pos;
	if(m_table == nullptr) {
		qDebug("m_table null point"); 
		return;
	}
	QTableWidgetItem *item =m_table->itemAt(pos);

	if(!m_pMenu) {
		delete m_pMenu;
	}
	m_pMenu = new QMenu;
	m_pMenu->setStyleSheet("QMenu {background-color:#F2F2F2;} QMenu::item {padding-left:4px;width:100px;height:25px;} QMenu::item::selected {background-color: #999999;}");
	
	if(item != nullptr) {
		m_pEditAction = new QAction(this);
		m_pEditAction->setText(QString::fromLocal8Bit("编辑"));
		m_pDeleteAction = new QAction(this);
		m_pDeleteAction->setText(QString::fromLocal8Bit("删除"));

		m_pMenu->addAction(m_pEditAction);
		m_pMenu->addAction(m_pDeleteAction);

		connect(m_pEditAction,SIGNAL(triggered(bool)),this,SLOT(onEditEvent()));
		connect(m_pDeleteAction,SIGNAL(triggered(bool)),this,SLOT(onDeleteEvent()));

		m_pMenu->exec(QCursor::pos());
	}
}

void MainWdg::onEditEvent() {
	m_opModel = 2;
	QTableWidgetItem *item =m_table->itemAt(*m_pPoint);
	m_currentRow = item->row();
	
	auto *factoryDlg = new FactoryDlg;
	connect(factoryDlg,SIGNAL(onData(Vendors)),this,SLOT(onData(Vendors)));
	qDebug() << this->m_vendorList.size();
	Vendors *ven = this->m_vendorList.at(m_currentRow);
	factoryDlg->setData(*ven);
	factoryDlg->show();
}

void MainWdg::onDeleteEvent() {
	QTableWidgetItem *item =m_table->itemAt(*m_pPoint);
	int row = item->row();
	Vendors *ven = m_vendorList.at(row);
	deleteVendor(*ven);
	/*m_factorydb->deleteFactory(ven);
	QList<Vendors *> vendorList = m_factorydb->queryAllFactory();
	setVendorList(vendorList);*/
}

void MainWdg::deleteVendor(Vendors vendor) {
	m_pVendors = vendor;
	QString url = QString(URL_DEL_FACTORY).arg(vendor.serverId);
	m_pHttpNetwork->get(url);
}

void MainWdg::setVendorList(QList<Vendors*> list) {
	this->m_vendorList = list;
	m_table->setRowCount(m_vendorList.size());
	for (int i = 0;i<m_vendorList.size();i++)
	{
		int col = 0;
		Vendors* vend = m_vendorList.at(i);

		auto* item = new QTableWidgetItem(vend->vendorName);
		item->setData(Qt::UserRole,vend->vendorFactory);
		m_table->setItem(i,col++,item);
		m_table->setItem(i,col++,new QTableWidgetItem(vend->vendorLoginName));
		m_table->setItem(i,col++,new QTableWidgetItem(""));

		// TCL厂家，手动登陆
		if (vend->vendorFactory == FACTORY_TCL)
		{
			auto *btn = new QPushButton();
			btn->setProperty(PROPERTY_ID,vend->serverId);
			btn->setStyleSheet("QPushButton { \
						  border:0px;\
						  background-color:white;\
						  color:#0094FF;\
						  height:24px;\
						  }\
						  QPushButton::pressed {\
						  background-color:#0094FF;\
						  border:0px;\
						  color: white;\
						  }\
						  QPushButton::hover {\
						  background-color:#0094FF;\
						  border:0px;\
						  color: white;\
						  }\
						  ");

			btn->setText("登录");
			m_table->setCellWidget(i,col,btn);
			if(isLogin(*vend)) {
				QTableWidgetItem* itemState = m_table->item(i,2);
				itemState->setText("登录成功");
				itemState->setTextColor(Qt::green);
				btn->setEnabled(false);
			} else {
				connect(btn,SIGNAL(pressed()),this,SLOT(onLogin()));
			}
		}
		else
		{
			if(isLogin(*vend)) {
				QTableWidgetItem* itemState = m_table->item(i,2);
				itemState->setText("登录成功");
				itemState->setTextColor(Qt::green);
			} else {
				m_table->item(i, 2)->setText("登录中...");
				m_table->removeCellWidget(i,3);
				m_pLoginHelper->enqueue(*vend);
			}
		}
	}
}

void MainWdg::checkLogin(Vendors* vend)
{
	QString json = QString("{\"user\":\"%1\",\"pwd\":\"%2\",\"factory\":\"%3\",\"mainServerHost\":\"%4\",\"statusReportHost\":\"%5\",\"seqno\":\"%6\"}")
		.arg(vend->vendorLoginName)
		.arg(vend->vendorPassword)
		.arg(vend->vendorFactory)
		.arg(URL_MAIN_SERVER)
		.arg(URL_REPT)
		.arg("1");
	QByteArray req ;
	req.append(json.toUtf8());
	QhttpNetwork::instance()->post(URL_FACTORY_LONGIN,req);
	qDebug() << "json:" << json;
	qDebug("向自动登录接口发送内容:%s",json.toStdString().c_str());
}


void MainWdg::factoryReplyData(QByteArray data) {
	QString msg = QString::fromUtf8(data.data());
	qDebug() << msg;

	Json::Reader reader;
	Json::Value value;

	if(reader.parse(string(data.data()),value))
	{
		string code = value["code"].asString();
		string flag = value["flag"].asString();
		if (flag == "addFactoryAccount") {
			if(code == "200") {
				// 检查厂家账号是否已经添加了
				if(m_pVendors.id != 0){
					m_factorydb->updateFactory(&m_pVendors);
					updateVendorInfo(&m_pVendors);
				} else {
					string id = value["data"].asString();
					m_pVendors.serverId = QString::fromLocal8Bit(id.c_str());
					Vendors queryResult;
					m_factorydb->queryFactoryByUsername(m_pVendors.vendorLoginName,m_pVendors.vendorFactory,m_pVendors.sfAccount,&queryResult);
					if (queryResult.serverId != "") {
						QMessageBox::warning(this,QString::fromLocal8Bit("警告"),"请不要添加重复的账号",QMessageBox::Yes,QMessageBox::Yes);
						return;
					}
					int insertId = m_factorydb->insertFactory(&m_pVendors);
					if (insertId == -1) {
						return;
					}
					m_pVendors.id = insertId;
					insertVendorInfo(&m_pVendors);
				}
			} else if (code == "423") {
				QString content = QString::fromUtf8(value["msg"].asCString());
				QString errMsg = QString::fromUtf8(value["errMsg"].asCString());
				qDebug() << "添加厂家账号返回" << content << errMsg;
				if(content.isEmpty()) {
					QMessageBox::warning(this,QString::fromLocal8Bit("警告"),errMsg,QMessageBox::Yes,QMessageBox::Yes);
				} else {
					QMessageBox::warning(this,QString::fromLocal8Bit("警告"),content,QMessageBox::Yes,QMessageBox::Yes);
				}
			}
		} else if (flag == "delFactoryAccount") {
			if (code == "200") {
				m_factorydb->deleteFactory(&m_pVendors);
				deleteVendorInfo(&m_pVendors);
			}
		}else if (flag == "modFactoryAccount"){
			if (code == "200") {
				if(m_currentRow >= 0){
					QTableWidgetItem* itemName = m_table->item(m_currentRow,1);
					if (itemName != NULL)
					{
						itemName->setText(m_pVendors.vendorLoginName);
						Vendors *ven = this->m_vendorList.at(m_currentRow);
						ven->vendorLoginName = m_pVendors.vendorLoginName;
						ven->vendorPassword = m_pVendors.vendorPassword;
					}
				}
				QMessageBox::information(this,"工单助手","修改成功");
			}else{
				QMessageBox::warning(this,QString::fromLocal8Bit("警告"),"修改失败",QMessageBox::Yes,QMessageBox::Yes);
			}
		}
	}
}

void MainWdg::onLoginBack(string user,string factory,int status)
{
	QString userQ = QString::fromLocal8Bit(user.c_str());
	Vendors* vendor = new Vendors;
	int index = getVendorIndex(user, factory, vendor);
	if (index == -1) {
		return;
	}
	QTableWidgetItem* itemUser = m_table->item(index,1);
	QTableWidgetItem* itemState = m_table->item(index,2);
	
	switch (status)
	{
	case 1:
		itemState->setText("登陆成功");
		itemState->setTextColor(Qt::green);
		if(!isLogin(*vendor)) {
			m_loginedFactory.push_back(vendor);
		}
		m_table->removeCellWidget(index,3);
		break;
	case 422:
		itemState->setText(ERROR_ALREADY_LONGIN);
		itemState->setTextColor(Qt::red);
		this->addReLoginButton(index,3);
		break;
	case 423:
		itemState->setText(ERROR_PWD);
		itemState->setTextColor(Qt::red);
		this->addReLoginButton(index,3);
		break;
	case 404:
		itemState->setText("其他登录异常");
		itemState->setTextColor(Qt::red);
		this->addReLoginButton(index,3);
		break;
	case 424:
		itemState->setText("验证码错误");
		itemState->setTextColor(Qt::red);
		this->addReLoginButton(index,3);
		break;
	default:
		itemState->setText("登陆失败");
		itemState->setTextColor(Qt::red);
		this->addReLoginButton(index,3);
		break;
	}
}

int MainWdg::getVendorIndex(string username,string factory,Vendors *vendor) {
	int index = -1;
	auto usernameQ = QString::fromLocal8Bit(username.c_str());
	auto factoryQ = QString::fromLocal8Bit(factory.c_str());
	QMutableListIterator<Vendors *> iterator(m_vendorList);
	while(iterator.hasNext()) {
		index++;
		Vendors * vend = iterator.next();
		if (usernameQ == vend->vendorLoginName && factoryQ == vend->vendorFactory) {
			if (vendor != nullptr) {
				vendor->id = vend->id;
				vendor->serverId = vend->serverId;
				vendor->sfAccount = vend->sfAccount;
				vendor->vendorFactory = vend->vendorFactory;
				vendor->vendorLoginName = vend->vendorLoginName;
				vendor->vendorName = vend->vendorName;
				vendor->vendorPassword = vend->vendorPassword;
				vendor->vendorUrl = vend->vendorUrl;
			}
			return index;
		}
	}
	return -1;
}

void MainWdg::parserSession(Json::Value & jvalue)
{
	string status = jvalue["status"].asString();
	if (!(status == RESULT_TRUE))
	{
		string user = jvalue["user"].asString();
		string factory = jvalue["factory"].asString();
		int row = m_table->rowCount();
		for (int i = 0;i<row;i++)
		{
			QTableWidgetItem* itemFactory = m_table->item(i,0);
			QTableWidgetItem* itemUser = m_table->item(i,1);
			string ftext = itemFactory->data(Qt::UserRole).toString().toStdString();
			string fuser = itemUser->text().toStdString();
			if (fuser == user && ftext == factory)
			{
				QTableWidgetItem* itemStatus = m_table->item(i,2);
				itemStatus->setText("会话过期，请重新登录");
				itemStatus->setTextColor(Qt::red);
				m_table->cellWidget(i,3)->setEnabled(true);

				// 显示窗口
				//showNormal();
			}
		}
		if (factory == FACTORY_MEDIA)
		{
			// 清除sestion过期标志
			sendRmSessionTimeout(user.c_str());
		}
	}
}

void MainWdg::sendRmSessionTimeout(QString user)
{
	QString json = QString("{\"user\":\"%1\",\"factory\":\"%2\"}")
		.arg(user)
		.arg(FACTORY_MEDIA);
	QByteArray req;
	req.append(json);
	QhttpNetwork::instance()->post(URL_REMOVE_SESSION_TIMEOUT,req);

	qDebug("发送session过期命令:%s",json.toStdString().c_str());
}

void MainWdg::loginResp(Json::Value& jvalue)
{
	string user = jvalue["user"].asString();
	string factory = jvalue["factory"].asString();
	int row = getVendorIndex(user,factory,nullptr);
	QTableWidgetItem* item = m_table->item(row,2);
	if (item == nullptr)
	{
		return;
	}
	QWidget* btn = m_table->cellWidget(row,3);
	
	string sucess = jvalue["success"].asString();
	if (sucess == RESULT_TRUE)
	{
		// 登录成功

		item->setText("登录成功");
		item->setTextColor(Qt::green);

		if (!m_sesstionChecker->isActive())
		{
			// 启动sestion过期检查
			m_sesstionChecker->start();
		}

		if (btn != nullptr)
		{
			btn->setVisible(false);
		}
	}
	else
	{
		int code = jvalue["code"].asInt();
		if (code == 423)
		{
			item->setText(ERROR_PWD);
		}
		else if (code == 424)
		{
			item->setText("验证码过期");
		}
		else
		{
			item->setText("登录失败");
		}
		item->setTextColor(Qt::red);
	}
}

void MainWdg::onLogin()
{
	QObject* obj = sender();
	if (obj != nullptr)
	{
		QString serverId = obj->property(PROPERTY_ID).toString();
		Vendors vendor;
		int row = getVendorInfoById(serverId,&vendor);
		if (row == -1) {
			return;
		}
		m_flogin.setContext(row,vendor.vendorFactory,vendor.vendorLoginName,vendor.vendorPassword);
	}
	m_flogin.showDlg();
}

int MainWdg::getVendorInfoById(QString id,Vendors *vendor) {
	int index = -1;
	QMutableListIterator<Vendors *> iterator(m_vendorList);
	while(iterator.hasNext()) {
		index++;
		Vendors * vend = iterator.next();
		if (id == vend->serverId) {
			if (vendor != nullptr) {
				vendor->id = vend->id;
				vendor->serverId = vend->serverId;
				vendor->sfAccount = vend->sfAccount;
				vendor->vendorFactory = vend->vendorFactory;
				vendor->vendorLoginName = vend->vendorLoginName;
				vendor->vendorName = vend->vendorName;
				vendor->vendorPassword = vend->vendorPassword;
				vendor->vendorUrl = vend->vendorUrl;
			}
			return index;
		}
	}
	return -1;
}

void MainWdg::insertIntoTable(Vendors* vendor, int row) {
	int col = 0;
	auto* item = new QTableWidgetItem(vendor->vendorName);
	item->setData(Qt::UserRole,vendor->vendorFactory);
	m_table->setItem(row,col++,item);
	m_table->setItem(row,col++,new QTableWidgetItem(vendor->vendorLoginName));
	

	// TCL厂家，手动登陆
	if (vendor->vendorFactory == FACTORY_TCL)
	{
		m_table->setItem(row,col++,new QTableWidgetItem(""));
		auto *btn = new QPushButton();
		btn->setProperty(PROPERTY_ID,vendor->serverId);
		btn->setStyleSheet("QPushButton { \
						   border:0px;\
						   background-color:white;\
						   color:#0094FF;\
						   height:24px;\
						   }\
						   QPushButton::pressed {\
						   background-color:#0094FF;\
						   border:0px;\
						   color: white;\
						   }\
						   QPushButton::hover {\
						   background-color:#0094FF;\
						   border:0px;\
						   color: white;\
						   }\
						   ");

		btn->setText("登录");
		m_table->setCellWidget(row,col,btn);
		if(isLogin(*vendor)) {
			QTableWidgetItem* itemState = m_table->item(row,2);
			itemState->setText("登录成功");
			itemState->setTextColor(Qt::green);
			btn->setEnabled(false);
		} else {
			connect(btn,SIGNAL(pressed()),this,SLOT(onLogin()));
		}
	}
	else
	{
		if(isLogin(*vendor)) {
			QTableWidgetItem* itemState = m_table->item(row, 2);
			itemState->setText("登录成功");
			itemState->setTextColor(Qt::green);
		} else {
			m_table->setItem(row,col++,new QTableWidgetItem("登录中..."));
			m_pLoginHelper->enqueue(*vendor);
		}
	}
}

void MainWdg::insertVendorInfo(Vendors* vendor) {
	m_table->setRowCount(m_vendorList.size() + 1);
	insertIntoTable(vendor, m_vendorList.size());
	Vendors* vend = new Vendors;
	vend->id = vendor->id;
	vend->serverId = vendor->serverId;
	vend->vendorFactory = vendor->vendorFactory;
	vend->vendorLoginName = vendor->vendorLoginName;
	vend->vendorName = vendor->vendorName;
	vend->vendorPassword = vendor->vendorPassword;
	vend->vendorUrl = vendor->vendorUrl;
	m_vendorList.push_back(vend);
}

bool MainWdg::isLogin(Vendors vendor) {
	QMutableListIterator<Vendors *> iterator(m_loginedFactory);
	while(iterator.hasNext()) {
		Vendors* vend = iterator.next();
		if(vendor.serverId == vend->serverId) {
			return true;
		}		
	}
	return false;
}

void MainWdg::updateVendorInfo(Vendors* vendor) {
	int index = getVendorInfoById(vendor->serverId, nullptr);
	if (index == -1) {
		return;
	}
	if(m_table->rowCount() < index) {
		return;	
	}
	Vendors * ven = m_vendorList.at(index);
	ven->serverId = vendor->serverId;
	ven->vendorFactory = vendor->vendorFactory;
	ven->vendorLoginName = vendor->vendorLoginName;
	ven->vendorName = vendor->vendorName;
	ven->vendorPassword = vendor->vendorPassword;
	ven->vendorUrl = vendor->vendorUrl;

	auto factory_cell = m_table->item(index, 0);
	if (factory_cell != nullptr) {
		factory_cell->setText(vendor->vendorName);
	}
	auto username_cell = m_table->item(index, 1);
	if (username_cell != nullptr) {
		username_cell->setText(vendor->vendorLoginName);
	}
	if (vendor->vendorFactory == FACTORY_TCL) {
		m_table->setItem(index,2,new QTableWidgetItem(""));
		auto *btn = new QPushButton();
		btn->setProperty(PROPERTY_ID,vendor->serverId);
		btn->setStyleSheet("QPushButton { \
						   border:0px;\
						   background-color:white;\
						   color:#0094FF;\
						   height:24px;\
						   }\
						   QPushButton::pressed {\
						   background-color:#0094FF;\
						   border:0px;\
						   color: white;\
						   }\
						   QPushButton::hover {\
						   background-color:#0094FF;\
						   border:0px;\
						   color: white;\
						   }\
						   ");

		btn->setText("登录");
		m_table->setCellWidget(index,3,btn);
		connect(btn,SIGNAL(pressed()),this,SLOT(onLogin()));
		removeFromLogined(*vendor);
	} else {
		auto status_cell = m_table->item(index, 2);
		if (status_cell != nullptr) {
			status_cell->setText("登录中...");
			m_pLoginHelper->enqueue(*vendor);
		}
		removeFromLogined(*vendor);
	}
}

void MainWdg::removeFromLogined(Vendors vendor) {
	int index = 0;
	QMutableListIterator<Vendors *> iterator(m_loginedFactory);
	while(iterator.hasNext()) {
		Vendors* ven = iterator.next();
		if(ven->serverId == vendor.serverId) {
			m_loginedFactory.removeAt(index);
			return;
		}
		index ++;
	}
}

void MainWdg::deleteVendorInfo(Vendors* vendor) {
	int index = getVendorInfoById(vendor->serverId,nullptr);
	if (index == -1) {
		return;
	}
	m_vendorList.removeAt(index);
	if (m_table->rowCount() < index) {
		return;
	}
	m_table->removeRow(index);
}

void MainWdg::loging(string username,string factory)
{
	int row = getVendorIndex(username,factory,nullptr);
	if (row == -1) {
		return;
	}
	QTableWidgetItem* item = m_table->item(row,2);
	if (item != nullptr)
	{
		item->setText("登录中...");
		item->setTextColor(Qt::green);
	}
}

void MainWdg::sesstionChecker()
{
	for (int i = 0;i<m_vendorList.size();i++)
	{
		Vendors * vend = m_vendorList.at(i);
		if (vend->vendorFactory == FACTORY_MEDIA)
		{
			this->sendSessionChecker(vend);
		}
	}
}

void MainWdg::sendSessionChecker(Vendors *vender)
{
	QString json = QString("{\"user\":\"%1\",\"factory\":\"%2\"}")
		.arg(vender->vendorLoginName)
		.arg(vender->vendorFactory);
	QByteArray req ;
	req.append(json);
	QhttpNetwork::instance()->post(URL_SESSION_CHECK,req);
	qDebug("发送session过期检查命令:%s",json.toStdString().c_str());
}

void MainWdg::refreshVendorList() {
	m_vendorList = m_factorydb->queryAllFactory(Configer::instance()->getUser());
	setVendorList(m_vendorList);
}

void MainWdg::addReLoginButton(int row, int col)
{
	auto relogin_button = new QPushButton;
	Vendors* vend = m_vendorList.at(row);
	relogin_button->setProperty(PROPERTY_ID,vend->serverId);
	relogin_button->setStyleSheet("QPushButton { \
					   border:0px;\
					   background-color:white;\
					   color:#2196F3;\
					   height:24px;\
					   }\
					   QPushButton::pressed {\
					   background-color:#2196F3;\
					   border:0px;\
					   color: white;\
					   }\
					   QPushButton::hover {\
					   background-color:#2196F3;\
					   border:0px;\
					   color: white;\
					   }\
					   ");
	relogin_button->setText("重新登录");
	m_table->setCellWidget(row,col,relogin_button);
	connect(relogin_button,SIGNAL(pressed()),this,SLOT(onReLoginButtonClick()));
}

void MainWdg::onReLoginButtonClick(){
	Vendors vendor;
	QObject * button = sender();
	auto serverId = button->property(PROPERTY_ID).toString();
	int row = getVendorInfoById(serverId, &vendor);
	if (row == -1) {
		return;
	}
	m_table->item(row, 2)->setText("重新登录中...");
	m_table->item(row, 2)->setTextColor(QColor(0,0,0));
	m_pLoginHelper->enqueue(vendor);
}