#include "factorydb.h"
#include "qdesktopservices.h"

FactoryDB::FactoryDB(QObject *parent)
	: QObject(parent)
{
	// 创建数据表
	createDatabase();
}

FactoryDB::~FactoryDB()
{

}

int FactoryDB::insertFactory(Vendors* vendors) {
	QSqlDatabase db = open();
	QSqlQuery query(db);
	
	QString insert_sql = QString("insert into factory('sf_account','factory_name','factory','username','password','serverId') values(?,?, ?, ?, ?,?)");
	query.prepare(insert_sql);
	query.addBindValue(vendors->sfAccount);
	query.addBindValue(vendors->vendorName);
	query.addBindValue(vendors->vendorFactory);
	query.addBindValue(vendors->vendorLoginName);
	query.addBindValue(vendors->vendorPassword);
	query.addBindValue(vendors->serverId);

	if(!query.exec()) {
		qDebug() << "插入数据失败," << query.lastError();
	} else {
		qDebug() << "插入数据成功";
		query.prepare("select last_insert_rowid() from factory");
		if(!query.exec()) {
			qDebug() << "获取最新插入的id失败" << query.lastError();
			return -1;
		} else {
			if (query.next()) {
				return query.value(0).toInt();
			}
		}
	}
	close(db);
	return -1;
}

void FactoryDB::updateFactory(Vendors* ven) {
	QSqlDatabase db = open();
	QSqlQuery query(db);

	QString update_sql = QString("update factory set factory_name=:factory_name,username=:username,password=:password,factory=:factory where id=:id and sf_account=:sf_account");
	query.prepare(update_sql);
	query.bindValue(":factory_name",ven->vendorName);
	query.bindValue(":username",ven->vendorLoginName);
	query.bindValue(":password",ven->vendorPassword);
	query.bindValue(":id",ven->id);
	query.bindValue(":factory",ven->vendorFactory);
	query.bindValue(":sf_account",ven->sfAccount);
	if(!query.exec()) {
		qDebug() << "更新厂家数据失败," << query.lastError();
	} else {
		qDebug() << "更新厂家数据成功";
	}
	close(db);
}

void FactoryDB::deleteFactory(Vendors* ven) {
	QSqlDatabase db = open();
	QSqlQuery query(db);
	QString delete_sql = QString("delete from factory where serverId = ?");
	query.prepare(delete_sql);
	query.addBindValue(ven->serverId);
	if(!query.exec()) {
		qDebug() << "删除厂家数据失败," << query.lastError();
	} else {
		qDebug() << "删除厂家数据成功";
	}
	close(db);
}

int FactoryDB::clearFactory() {
	QSqlDatabase db = open();
	QSqlQuery query(db);
	QString sql = QString("delete from factory");
	query.prepare(sql);
	if(query.exec()) {
		qDebug() << "删除厂家数据失败" << query.lastError();
		return -1;
	} else {
		qDebug() << "清空厂家数据成功";
		return 0;
	}
	close(db);
}

QList<Vendors *> FactoryDB::queryAllFactory(QString accountName) {
	QList<Vendors *> vendorList;
	QSqlDatabase db =open();
	QSqlQuery query(db);
	QString query_all_sql = QString("select * from factory where sf_account = :sf_account");
	query.prepare(query_all_sql);
	query.bindValue(":sf_account",accountName);
	
	if(!query.exec()) {
		qDebug() << "查询失败:" << query.lastError();
	} else {
		while (query.next())
		{
			int id = query.value(0).toInt();
			QString factory_name = query.value(1).toString();
			QString factory = query.value(2).toString();
			QString username = query.value(3).toString();
			QString password = query.value(4).toString();
			QString serverId = query.value(5).toString();
			QString sf_account = query.value(6).toString();
			Vendors * ven = new Vendors;
			ven->id = id;
			ven->vendorName = factory_name;
			ven->vendorFactory = factory; 
			ven->vendorLoginName = username;
			ven->vendorPassword = password;
			ven->serverId = serverId;
			ven->sfAccount = sf_account;
			vendorList.push_back(ven);
		}
	}
	close(db);
	return vendorList;
}

void FactoryDB::queryFactoryByUsername(QString username,QString factory,QString accoutName,Vendors *ven) {
	QSqlDatabase db = open();
	QSqlQuery query(db);
	QString query_sql = QString("select * from factory where username=? and factory=? and sf_account=?");
	query.prepare(query_sql);
	query.addBindValue(username);
	query.addBindValue(factory);
	query.addBindValue(accoutName);
	if (!query.exec()) {
		qDebug() << "查询失败:" << query.lastError();
		return;
	} else {
		if(query.first()) {
			int id = query.value(0).toInt();
			QString factory_name = query.value(1).toString();
			QString factory = query.value(2).toString();
			QString username = query.value(3).toString();
			QString password = query.value(4).toString();
			QString serverId = query.value(5).toString();
			QString sf_account = query.value(6).toString();
			ven->id = id;
			ven->vendorName = factory_name;
			ven->vendorFactory = factory; 
			ven->vendorLoginName = username;
			ven->vendorPassword = password;
			ven->serverId = serverId;
			ven->sfAccount = sf_account;
		}
	}
}

int FactoryDB::getLastInsertId() {
	QSqlDatabase db = open();
	QSqlQuery query(db);
	QString sql = QString("select last_insert_rowid() from factory");
	query.prepare(sql);
	if(!query.exec()) {
		return -1;
	} else {
		if(query.first()){
			int id = query.value(0).toInt();
			return id;
		}
	}
	return -1;
}

void FactoryDB::createDatabase() {
	QSqlDatabase db = open();

	QSqlQuery query(db);
	QString check_table_sql = QString("select count(*) from sqlite_master where type='table' and name = '%1'").arg("factory");
	query.prepare(check_table_sql);
	query.exec();
	if(query.next()) {
		if(query.value(0).toInt() != 0) {
			qDebug() << "数据库已经存在.";
		} else {
			qDebug() << "即将创建数据库.";
			QString create_table_sql = QString("create table factory(id integer primary key autoincrement,\
											   factory_name text not null,\
											   factory text not null,\
											   username text not null,\
											   password text not null,\
											   serverId text,\
											   sf_account text\
											   )");
			query.prepare(create_table_sql);
			if(!query.exec()) {
				qDebug() << "Create database factory fail!" << query.lastError();
			} else {
				qDebug() << "Create database factory success!";
			}
		}
	}
	close(db);
}

QSqlDatabase FactoryDB::open() {
	QSqlDatabase database;
	if(QSqlDatabase::contains("qt_sql_default_connection")) {
		database = QSqlDatabase::database("qt_sql_default_connection");
	} else {
		database = QSqlDatabase::addDatabase("QSQLITE");
		database.setDatabaseName("Factory.db");
		database.setUserName("SF123");
		database.setPassword("123456");
	}
	if(!database.open()) {
		qDebug() << "无法连接数据库";
		return database;
	}

	return database;
}

void FactoryDB::close(QSqlDatabase database) {
	database.close();
}


