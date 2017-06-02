#include "playthread.h"

PlayThread::PlayThread()
{
	m_isPlaying = false;
}

void PlayThread::enqueue(int id)
{
	qDebug("begin enqueue");
	m_mutex.tryLock();
	m_queue.enqueue(id);
	m_mutex.unlock();
	qDebug("end enqueu");

}

int PlayThread::dequeue()
{
	
	int id = -1;
	m_mutex.tryLock();
	if (!m_queue.isEmpty())
	{
		qDebug("begin dequeue");
		id = m_queue.dequeue();
		qDebug("end dequeue");
	}
	m_mutex.unlock();
	
	return id;
}

void PlayThread::beginPlay()
{
	qDebug("beginPlay");
	m_isPlaying = false;
}

void PlayThread::run()
{
	while(true)
	{
		if (!m_isPlaying)
		{
			int id = dequeue();
			if (id >=0)
			{
				m_isPlaying = true;
				emit play(id);
				qDebug("emit play ");
			}
		}
		
		msleep(10);
	}
}

