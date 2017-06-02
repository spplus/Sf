#include <QThread>
#include <QMutex>
#include <QQueue>
class PlayThread	:public QThread
{
	Q_OBJECT
public:
	PlayThread();
	void	enqueue(int id);
	int 	dequeue();
public slots:
	// ���̲߳�����ɺ󣬷���Ϣ֪ͨ�����̼߳������Ŷ�������һ����
	void	beginPlay();		
	
signals:
	void	play(int id);

protected:
	void	run();

private:
	bool			m_isPlaying;
	QMutex			m_mutex;
	QQueue<int>		m_queue;	
};