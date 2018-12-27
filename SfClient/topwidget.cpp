#include <QtGui>
#include "topwidget.h"

TopWidget::TopWidget(QWidget* parent/* =NULL */)
	:QDialog(parent)
{
	QHBoxLayout * hbox = new QHBoxLayout;
	QToolButton *closeBtn = new QToolButton;
	closeBtn->setAutoRaise(true);
	closeBtn->setIcon(QIcon(":images/close.png"));
	closeBtn->setFixedSize(32,32);
	closeBtn->setObjectName("closeBtn");
	hbox->addStretch();
	hbox->addWidget(closeBtn);
	
	QVBoxLayout*  vbox = new QVBoxLayout;
	vbox->addLayout(hbox);
	vbox->addStretch();
	this->setLayout(vbox);

	connect(closeBtn,SIGNAL(pressed()),qApp,SLOT(quit()));

	QPixmap pixmap = QPixmap(":images/title.png");
	QPalette  palette (this->palette());
	palette.setBrush(QPalette::Background, QBrush(pixmap));
	this->setPalette( palette );
	setAutoFillBackground(true);
	vbox->setMargin(0);
	hbox->setMargin(0);
	this->setMinimumHeight(165);
	
}