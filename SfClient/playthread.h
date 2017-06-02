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
	// 主线程播放完成后，发消息通知播放线程继续播放队列中下一个。
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