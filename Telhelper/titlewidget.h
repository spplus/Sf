#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

class QLabel;
class myPushButton;

class titleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit titleWidget(QWidget *parent = 0);
    
signals:
    void myClose();

public:
    void setTitleText(QString title);
private:
    QLabel *titleText;//��������
    myPushButton *btnClose;//����رհ�ť

protected:
    void paintEvent(QPaintEvent *);
};

#endif // TITLEWIDGET_H
