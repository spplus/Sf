#ifndef __GOCONTROLLER_H__
#define __GOCONTROLLER_H__

#include <QProcess>
#include <QDebug>
#include <QStringList>

class GoController
{
public:
	static GoController*		instance();
	void						goRun(QString path);
	void						goExit();
	QProcess::ProcessState		getState();
private:
	GoController();
	bool						getProcess(QString);

private:
	QProcess					m_pro;
	static GoController*		m_inst;

};

#endif