#include "maincontroller.h"
#include <QCoreApplication>
#include <QTextStream>

MainController::MainController(QObject *parent) : QObject(parent)
{
    mSelf = this;
}

MainController::~MainController() {
    delete mSelf;
}

MainController *MainController::mSelf = nullptr;
UBOX_HANDLE MainController::mDevice = -1;
QFile *MainController::file = nullptr;
QString MainController::mPhoneNumber = nullptr;

void WINAPI MainController::eventCallback(UBOX_HANDLE uboxHnd,                  //设备句柄
                                          int eventID,                          //事件，参考UBOX_EVENT的定义
                                          long unsigned int param1,             //下面几个参数不同的事件，其含义不同
                                          long unsigned int param2,
                                          long unsigned int param3,
                                          long unsigned int param4) {
    Q_UNUSED(param4);

    QTextStream out(stdout);
    QString newPhone;
    cout << "Event Id:" << eventID << ";" << uboxHnd << endl;
    switch (eventID) {
    case UBOX_EVENT_DEVICE_PLUG_IN:
        // 设备接入
        cout << "Device plug in!" << endl;
        mDevice = uboxHnd;
        emit mSelf->sendToTextArea("******* 设备已经连接 *******");
        mSelf->getDeviceInfo();
        break;
    case UBOX_EVENT_DEVICE_PLUG_OUT:
        // 设备被拔出
        emit mSelf->sendToTextArea("******* 弹屏设备已被弹出 *******");
        cout << "Device plug out!" << endl;
        break;
    case UBOX_EVENT_ALARM:
        // 设备报警
        cout << "Alarm" << endl;
        break;
    case UBOX_EVENT_DEVICE_ERROR:
        cout << "Device open error !" << endl;
        break;
    case UBOX_EVENT_LINE_RINGING:
        // 电话开始响铃
        cout << "Telephone ringing!!!" << endl;
        break;
    case UBOX_EVENT_LINE_RING_STOP:
        // 电话响铃停止
        cout << "Telephone ring stop!!!" << endl;
        break;
    case UBOX_EVENT_LINE_HOOK_UP:
        // 电话挂机
        cout << "Telephone hook up" << endl;
        mPhoneNumber = nullptr;
        mSelf->stopStreamRecord();
        break;
    case UBOX_EVENT_LINE_HOOK_OFF:
        // 电话摘机 此时可开始录音
        cout << "Telephone hook off" << endl;
        if(mPhoneNumber != nullptr) {
            mSelf->startStreamRecord(mPhoneNumber,true);
        }
        break;
    case UBOX_EVENT_LINE_HANG:
        // 电话机线路悬空
        cout << "Telephone hang" << endl;
        break;
    case UBOX_EVENT_RING_CANCEL:
        // 电话振铃取消
        cout << "Telephone ring cancel" << endl;
        break;
    case UBOX_EVENT_LINE_VOLTAGE:
        // 返回线路电压检测结果
        cout << "Got voltage" << endl;
        break;
    case UBOX_EVENT_STREAM_VOICE:
        // 返回录音数据包
        cout << "Got voice" << endl;
        break;
    case UBOX_EVENT_CALLER_ID:
        // 返回来电号码
        cout << "Phone number ========" << endl;
        cout << "Number:" << (char*)param1 << endl;
        mPhoneNumber = QString((char*)param1);
        emit mSelf->sendToTextArea("******* 电话接入 *******");
        newPhone.append("来电号码:").append(&mPhoneNumber);
        out << newPhone << endl;
        emit mSelf->sendToTextArea(newPhone);
        emit mSelf->startRing((char*)param1);
        cout << "Time:" << (char*)param2 << endl;
        cout << "Name:" << (char*)param3 << endl;
        break;
    case UBOX_EVENT_DTMF_DOWN:
        // 返回用户按键
        cout << "User press button" << endl;
        cout << "Button:" << (char)param1 << endl;
        if(mPhoneNumber == nullptr) {
            mPhoneNumber = QString((char)param1);
        } else {
            mPhoneNumber.append((char)param1);
        }
        emit mSelf->stopTimerSignal();
        emit mSelf->startTimerSignal();
        break;
    case UBOX_EVENT_DTMF_UP:
        // 用户按键释放 暂时没有作用
        cout << "User release button press" << endl;
        break;
    case UBOX_EVENT_DEVICE_PLAY_END:
        // 放音结束
        cout << "Play end" << endl;
        break;
    case UBOX_EVENT_DEVICE_PLAY_ERROR:
        // 放音错误
        cout << "Play error" << endl;
        break;
    case UBOX_EVENT_DEVICE_BUSY_TONE:
        // 忙音 表示用户已经挂机
        cout << "Busy tone" << endl;
        break;
    case UBOX_EVENT_POLARITY:
        // 极性反转 需要向电信部门申请
        cout << "polarity" << endl;
        break;
    }

}

int MainController::openDevice() {
    int ret = ubox_open(eventCallback,UBOX_MODE_RECORD);
    dealMethodCode(ret);
    return ret;
}

void MainController::closeDevice() {
    ubox_close();
}

void MainController::getDeviceInfo() {
    float version;
    char *product_name = NULL;
    int ret = ubox_get_device_versionnum(mDevice,version);
    dealMethodCode(ret);
    cout << "Version:" << version << endl;
    ret = ubox_get_product_ID(mDevice);
    dealMethodCode(ret);
    cout << "product Id:" << ret << endl;

    product_name = (char *)malloc(20);
    if(product_name == NULL) {
        return;
    }
    ret = ubox_get_product_name(mDevice,product_name);
    dealMethodCode(ret);
    for(int i = 0; i < 20;i++) {
        cout << *(product_name + i);
    }
    if(product_name != NULL) {
        free(product_name);
    }
}

void MainController::startStreamRecord(QString phoneNumber,bool in) {
    QTextStream out(stdout);
    out << phoneNumber << endl;
    //Settings *settings = new Settings;

    char section[] = "config";
    char key[] = "recordPath";
    char defaultValue[] = "";

    QString recordPath = QCoreApplication::applicationDirPath()+"/recordfile";
    QDir *dir = new QDir();
    if(!dir->exists(recordPath)) {
        if(!dir->mkpath(recordPath)) {
            // 创建文件夹失败
        }
    }
    if(!recordPath.endsWith("/")) {
        recordPath += "/";
    }
    if(in) {
        recordPath+= "IN_";
    }
    else
    {
        recordPath+= "OUT_";
    }
    recordPath += phoneNumber;
    recordPath += QDate::currentDate().toString("_yyyy_MM_dd_");
    recordPath += QTime::currentTime().toString("hh_mm_ss");
    recordPath += ".wav";

    out << recordPath << endl;
    cout << recordPath.toLatin1().data() << endl;
    int ret = ubox_record_file(mDevice,recordPath.toLatin1().data(),CODER_PCM);
    dealMethodCode(ret);
    cout << "Start record:" << ret << "," << mDevice << endl;
    if(!ret) {
        return;
    }
    cout << "start record" << endl;
}

void MainController::stopStreamRecord() {
    cout << "stop record" << endl;
    int ret = ubox_stop_record(mDevice);
    dealMethodCode(ret);
    emit sendToTextArea("录音完成");
}

void MainController::startRecord() {
    if(mPhoneNumber != nullptr) {
        QString str = QString("拨号:"+mPhoneNumber);
        // emit startRing(mPhoneNumber);
        emit sendToTextArea(str);
        startStreamRecord(mPhoneNumber,false);
    }
}

void MainController::dealMethodCode(int code) {
    switch (code) {
    case UBOX_ERR_SYSTEM:
        emit sendToTextArea("xxxxxxx 系统错误 xxxxxxx");
        break;
    case UBOX_ERR_DEVICE_NOT_FOUND:
        emit sendToTextArea("xxxxxxx 未发现弹屏设备 xxxxxxx");
        break;
    case UBOX_ERR_INVALID_HANDLE:
        emit sendToTextArea("xxxxxxx 无效的设备 xxxxxxx");
        break;
    case UBOX_ERR_INVALID_PARAMETER:
        emit sendToTextArea("xxxxxxx 不合法的参数 xxxxxxx");
        break;
    case UBOX_ERR_EXCEPTION:
        emit sendToTextArea("xxxxxxx 设备异常 xxxxxxx");
        break;
    case UBOX_ERR_INVALID_WORK_MODE:
        emit sendToTextArea("xxxxxxx 错误的工作模式 xxxxxxx");
        break;
    case UBOX_ERR_UBOX_NOT_OPEN:
        emit sendToTextArea("xxxxxxx 设备没有打开 xxxxxxx");
        break;
    case UBOX_ERR_CANNOT_CREATE_DIR:
        emit sendToTextArea("xxxxxxx 无法创建保存录音的文件夹 xxxxxxx");
        break;
    case UBOX_ERR_CANNOT_CREATE_FILE:
        emit sendToTextArea("xxxxxxx 无法创建录音文件 xxxxxxx");
        break;
    case UBOX_ERR_INVALID_VOICE_CODER:
        emit sendToTextArea("xxxxxxx 无效的录音编码 xxxxxxx");
        break;
    case UBOX_ERR_DEVICE_BUSY:
        emit sendToTextArea("xxxxxxx 设备繁忙 xxxxxxx");
        break;
    default:
        break;
    }
}
