
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
	QString program = "woodpeckerdn.exe";   
	QStringList arguments;  
	arguments << "debug"<<path;  
	m_pro.start(program, arguments);  
}

void GoController::goExit()
{
	m_pro.close();
}

