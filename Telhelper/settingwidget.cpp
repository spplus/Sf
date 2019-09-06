#include "settingwidget.h"
#include <QLabel>
#include "mypushbutton.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QLinearGradient>
#include <QIcon>
#include <QMessageBox>
#include <QFileDialog>

SettingWidget::SettingWidget(QDialog *parent) :
    QDialog(parent)
{
  
	QHBoxLayout* hboxnum = new QHBoxLayout;
	QHBoxLayout* hboxfile = new QHBoxLayout;
	QHBoxLayout* hboxmsg = new QHBoxLayout;
	QHBoxLayout* hboxcheck = new QHBoxLayout;
	QHBoxLayout* hboxbtn = new QHBoxLayout;

	// ���к�
	QLabel *numtitle = new QLabel("�豸���к�");
	numbEdit = new QLineEdit(this);
	hboxnum->addWidget(numtitle);
	hboxnum->addWidget(numbEdit);

	QLabel *filetile = new QLabel("¼������·��");
	pathEdit = new QLineEdit(this);
	QPushButton* btn = new QPushButton("...");
	btn->setFixedWidth(30);
	hboxfile->addWidget(filetile);
	hboxfile->addWidget(pathEdit,2);
	hboxfile->addWidget(btn);

	QLabel *msg = new QLabel("ע�⣺·����Ҫ��������");
	msg->setStyleSheet("color:rgb(255,0,0)}");
	hboxmsg->addStretch();
	hboxmsg->addWidget(msg);
	hboxmsg->addStretch();


	ispopup = new QCheckBox(this);
	ispopup->setText("ȥ���Ƿ���");
	ispopup->setChecked(true);
	hboxcheck->addStretch();
	hboxcheck->addWidget(ispopup);
	hboxcheck->addStretch();

	QPushButton* savebtn = new QPushButton("����");
	QPushButton* canclebtn = new QPushButton("ȡ��");
	hboxbtn->addStretch();
	hboxbtn->addWidget(savebtn);
	hboxbtn->addWidget(canclebtn);
	hboxbtn->addStretch();

    QVBoxLayout *layout=new QVBoxLayout;
    layout->addLayout(hboxnum);
	layout->addLayout(hboxfile);
	layout->addLayout(hboxmsg);
	layout->addLayout(hboxcheck);
	layout->addLayout(hboxbtn);

    setLayout(layout);
    //setFixedHeight(22);

	setWindowIcon(QIcon(":images/tray.png"));

	connect(savebtn,SIGNAL(pressed()),this,SLOT(save()));
	connect(canclebtn,SIGNAL(pressed()),this,SLOT(cancel()));
	connect(btn,SIGNAL(pressed()),this,SLOT(opendir()));

}

void SettingWidget::save(){
	
	QString num = numbEdit->text();
	QString path = pathEdit->text();
	int state = ispopup->checkState();
	if (num.isEmpty() || path.isEmpty())
	{
		QMessageBox::warning(this,"��ܰ��ʾ","����д�������ٱ���");
		return;
	}
	QString strAppPath = QCoreApplication::applicationDirPath();
	QString csFile = strAppPath + "/conf.ini";
	QSettings* Setting = new QSettings(csFile, QSettings::IniFormat);
	Setting->setValue("num",num);
	Setting->setValue("path",path);
	Setting->setValue("pop",state);

}

void SettingWidget::cancel(){
	this->accept();
}

void SettingWidget::opendir()
{
	//�ļ���·��
	QString srcDirPath = QFileDialog::getExistingDirectory(
		this, "��ѡ��Ŀ¼",
		"/");

	if (srcDirPath.isEmpty())
	{
		return;
	}
	else
	{
		pathEdit->setText(srcDirPath);

	}
}

