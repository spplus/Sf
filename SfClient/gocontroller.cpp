
#include "gocontroller.h"

GoController* GoController::m_inst = NULL;

GoController::GoController()
{
	
}

GoController* GoController::instance()
{
	if (m_inst == NULL)
	{
		m_inst = new GoController();
	}
	return m_inst;
}


void GoController::goRun(QString path)
{
	bool status = getProcess("woodpeckerdn.exe");
	if(status) {
		qDebug() << "��⵽����woodpeckerdn.exe��������,����������woodpeckerdn.exe����" << endl;
		return;
	}
	QString program = "woodpeckerdn.exe";   
	QStringList arguments;  
	arguments << "debug"<<path;  
	m_pro.start(program, arguments);
}

QProcess::ProcessState GoController::getState()
{
	return m_pro.state();
}

void GoController::goExit()
{
	m_pro.close();
}

bool GoController::getProcess(QString processName) {
	QProcess process;
	process.start("tasklist.exe");
	if(process.waitForFinished()) {
		QByteArray result = process.readAllStandardOutput();
		QString processList = result;
		if(processList.contains(processName)) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

