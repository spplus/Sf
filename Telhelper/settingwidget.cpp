#include "settingwidget.h"
#include <QLabel>
#include "mypushbutton.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QLinearGradient>
#include <QIcon>
#include <QCheckBox>
#include <QLineEdit>

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
	QLineEdit* numbEdit = new QLineEdit(this);
	hboxnum->addWidget(numtitle);
	hboxnum->addWidget(numbEdit);

	QLabel *filetile = new QLabel("¼������·��");
	QLineEdit *pathEdit = new QLineEdit(this);
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


	QCheckBox* ispopup = new QCheckBox(this);
	ispopup->setText("ȥ���Ƿ���");
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
}


