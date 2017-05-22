#ifndef __TITLEWIDGET_H__
#define __TITLEWIDGET_H__

#include <QtGui>
#include <Phonon/MediaObject>
#include <Phonon/MediaSource>
#include <Phonon/AudioOutput>

class TitleWidget	:public QDialog
{
	Q_OBJECT
public:
	TitleWidget(QWidget* parent = NULL);

public slots:
	void		sysExit();
	void		uploadFile();
	void		onlineHelp();
	void		proMgr();
private:
	void		initActions();
	void		initConnections();
	void		initMenu();
	QToolButton*	tbFactory(QString btnName);
private:
	QMenu*							m_fileMenu;
	QMenu*							m_helpMenu;
	QAction*						m_uploadLog;
	QAction*						m_exitAct;
	QAction*						m_onlineHelpAct;
	QAction*						m_authProAct;
};

#endif