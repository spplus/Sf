#ifndef FACTORYDB_H
#define FACTORYDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QDebug>

#include "common.h"

class FactoryDB : public QObject
{
	Q_OBJECT

public:
	FactoryDB(QObject *parent = 0);
	~FactoryDB();

	QList<Vendors*>				queryAllFactory(QString);
	int							insertFactory(Vendors*);
	void						updateFactory(Vendors*);
	void						deleteFactory(Vendors*);
	int							clearFactory();
	void						queryFactoryByUsername(QString,QString,QString,Vendors *);
	int							getLastInsertId();
private:
	QSqlDatabase				open();
	void						close(QSqlDatabase);
	void						createDatabase();
};

#endif // FACTORYDB_H
