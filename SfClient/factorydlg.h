#ifndef FACTORYDLG_H
#define FACTORYDLG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "common.h"

class FactoryDlg : public QDialog
{
	Q_OBJECT

public:
	FactoryDlg(QWidget *parent =0);
	~FactoryDlg();

	void setData(Vendors);

signals:
	void onData(Vendors);

public slots:
	void onConfirm();
	void onCancel();

private:
	QComboBox*			m_pComboBox;
	QLineEdit*			m_pUsername;
	QLineEdit*			m_pPassword;
	QLineEdit*			m_pUrl;
	QPushButton*		m_pConfirm;
	QPushButton*		m_pCancel;

	Vendors			m_vendors;
};

#endif // FACTORYDLG_H
