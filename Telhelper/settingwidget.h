#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QCoreApplication>
#include <QFile>
#include <QSettings>

class SettingWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SettingWidget(QDialog *parent = 0);

private slots:
	void	save();
	void	cancel();
	void	opendir();

private:
	QLineEdit* numbEdit;
	QLineEdit *pathEdit;
	QCheckBox* ispopup;
    
};

#endif // TITLEWIDGET_H
