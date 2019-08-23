#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QFile>
//#include <QQmlProperty>
//#include <QQmlComponent>
#include <QDate>
#include <QTime>
#include <QDir>
#include <QTimer>
#include <iostream>

extern "C" {
    #include <malloc.h>
}
#define TR(str)   (QString::fromLocal8Bit(str))
//#include "settings.h"
#include "phonic_ubox.h"
using namespace std;

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    int openDevice();
    void getDeviceInfo();
    void startStreamRecord(QString phoneNumber,bool in);
    void stopStreamRecord();

signals:
    void sendToTextArea(QString status);
    void startRing(QString phoneNumber);
    void startTimerSignal();
    void stopTimerSignal();

public slots:
    void closeDevice();
    void startRecord();

private:
    void dealMethodCode(int code);

    static void WINAPI eventCallback(UBOX_HANDLE uboxHnd,                    //设备句柄
                                     int eventID,                          //事件，参考UBOX_EVENT的定义
                                     long unsigned int param1,                 //下面几个参数不同的事件，其含义不同
                                     long unsigned int param2,
                                     long unsigned int param3,
                                     long unsigned int param4);
    static MainController *mSelf;
    static UBOX_HANDLE mDevice;
    static QFile *file;
    static QString mPhoneNumber;
};

#endif // MAINCONTROLLER_H
