#include "widget.h"
#include "titlewidget.h"
#include <QVBoxLayout>
#include "mypushbutton.h"
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);

    titleW=new titleWidget;
    connect(titleW,SIGNAL(myClose()),this,SLOT(close()));

    content=new QLabel;
    content->setWordWrap(true);
    content->setAlignment(Qt::AlignTop);
    content->setFixedSize(300,100);
    btnLook=new myPushButton();
	btnLook->setIcon(QIcon(":images/look.png"));
    connect(btnLook,SIGNAL(clicked()),this,SLOT(openWeb()));

    QVBoxLayout*mainLayout=new QVBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->addWidget(titleW);
    mainLayout->addWidget(content);
    content->setMargin(5);
    mainLayout->addWidget(btnLook,0,Qt::AlignRight);
    setLayout(mainLayout);

    setFixedSize(sizeHint().width(),sizeHint().height());

    timerShow=new QTimer(this);
    connect(timerShow,SIGNAL(timeout()),this,SLOT(myMove()));
    timerStay=new QTimer(this);
    connect(timerStay,SIGNAL(timeout()),this,SLOT(myStay()));
    timerClose=new QTimer(this);
    connect(timerClose,SIGNAL(timeout()),this,SLOT(myClose()));
}

Widget::~Widget()
{
}

void Widget::setMsg(QString title, QString content, QString url)
{
    titleW->setTitleText("  "+title);
    this->content->setText("   "+content);
    this->url=url;
}

void Widget::paintEvent(QPaintEvent *)
{
    QBitmap bitmap(this->size());
    bitmap.fill(Qt::white);
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(250,240,230)));
    painter.setPen(QPen(QBrush(QColor(255,222,173)),4));
    painter.drawRoundedRect(bitmap.rect(),5,5);
    setMask(bitmap);
}
void Widget::showAsQQ()
{
    QDesktopWidget *deskTop=QApplication::desktop();
    deskRect=deskTop->availableGeometry();

    normalPoint.setX(deskRect.width()-rect().width());
    normalPoint.setY(deskRect.height()-rect().height());
    move(normalPoint.x(),768-1);
    show();
    timerShow->start(5);
}
//ƽ����ʾ����
void Widget::myMove()
{
    static int beginY=QApplication::desktop()->height();
    beginY--;
    move(normalPoint.x(),beginY);
    if(beginY<=normalPoint.y())
    {
        timerShow->stop();
        timerStay->start(2000);
    }
}
//ͣ����ʾ
void Widget::myStay()
{
    static int timeCount=0;
    timeCount++;
    if(timeCount>=9)
    {
        timerStay->stop();
        timerClose->start(200);
    }
}
//�Զ��ر�ʱʵ�ֵ���Ч��
void Widget::myClose()
{
    static double tran=1.0;
    tran-=0.1;
    if(tran<=0.0)
    {
        timerClose->stop();
        emit close();
    }
    else
        setWindowOpacity(tran);
}
void Widget::openWeb()
{
    QDesktopServices::openUrl(QUrl(url));
}
