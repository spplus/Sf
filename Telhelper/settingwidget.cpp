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

	// 序列号
	QLabel *numtitle = new QLabel("设备序列号");
	numbEdit = new QLineEdit(this);
	hboxnum->addWidget(numtitle);
	hboxnum->addWidget(numbEdit);

	QLabel *filetile = new QLabel("录音保存路径");
	pathEdit = new QLineEdit(this);
	QPushButton* btn = new QPushButton("...");
	btn->setFixedWidth(30);
	hboxfile->addWidget(filetile);
	hboxfile->addWidget(pathEdit,2);
	hboxfile->addWidget(btn);

	QLabel *msg = new QLabel("注意：路径不要包含中文");
	msg->setStyleSheet("color:rgb(255,0,0)}");
	hboxmsg->addStretch();
	hboxmsg->addWidget(msg);
	hboxmsg->addStretch();


	ispopup = new QCheckBox(this);
	ispopup->setText("去电是否弹屏");
	ispopup->setChecked(true);
	hboxcheck->addStretch();
	hboxcheck->addWidget(ispopup);
	hboxcheck->addStretch();

	QPushButton* savebtn = new QPushButton("保存");
	QPushButton* canclebtn = new QPushButton("取消");
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
		QMessageBox::warning(this,"温馨提示","请填写完整后再保存");
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
	//文件夹路径
	QString srcDirPath = QFileDialog::getExistingDirectory(
		this, "请选择目录",
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

