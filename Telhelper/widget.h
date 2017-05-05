#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class titleWidget;
class myPushButton;
class QLabel;
class QTimer;

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void showAsQQ();//�����½���ʾ

public slots:
    void setMsg(QString title,QString content,QString url);

private slots:
    void openWeb();

    void myMove();
    void myStay();
    void myClose();
    
private:
    titleWidget *titleW;
    QLabel *content;
    myPushButton *btnLook;
    QString url;

    QPoint normalPoint;//��ȫ��ʾʱ���Ͻ�λ��
    QRect deskRect;

    QTimer *timerShow;//ƽ����ʾ�Ķ�ʱ��
    QTimer *timerStay;//ͣ��ʱ��Ķ�ʱ�� 10s
    QTimer *timerClose;//�رյ����Ķ�ʱ��

protected:
    void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
