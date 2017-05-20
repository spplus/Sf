#ifndef __GOCONTROLLER_H__
#define __GOCONTROLLER_H__

 #include <QProcess>

class GoController
{
public:
	static GoController*		instance();
	void						goRun(QString path);
	void						goExit();
private:
	GoController();

private:
	QProcess					m_pro;
	static GoController*		m_inst;

};

#endif