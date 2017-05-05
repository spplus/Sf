#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtGui>
#include <QMutex>
 #include <QWaitCondition>

#include "httpdownload.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

	MainWindow(QWidget* parent = NULL);
    ~MainWindow();

	void		doUpdate(QString url,QString appname,QString files);

public slots:


	// 更新进度条
	void		updateProgress( qint64 bytesReceived, qint64 bytesTotal );

	// 下载成功
	void		downloadSuccess(QString filename);

	// 发生错误
	void		replyError(QNetworkReply::NetworkError err);

private:
	void		afterUpdate();
	void		initWidget();
	void		execUpdate();
	void		rollbackUpdate();
	void		startMain();
private:

	// 升级地址
	QString			m_url;

	// 主程序名称
	QString			m_appName;

	// 工作目录
	QString			m_workDir;

	// 升级临时目录
	QString			m_tempDir;

	// 待下载列表
	QList<QString>	m_totalList;

	// 待下载列表
	QList<QString>	m_leftList;

	// 过程显示
	QLabel		*	m_info;

	// 进度条
	QProgressBar*	m_bar;
	HttpDownload*	m_httpDown;

};

#endif // MAINWINDOW_H
