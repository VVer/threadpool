#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include "pthread.h"
#include "locker.h"
template<typename T>
class threadpool
{
public:
	threadpool(int thread_number = 8, int max_requests = 10000);
	~threadpool();
	bool append(T* request);
private:
	//
	static void* worker(void* arg);
	void run();
private:
	int m_thread_number; //�̳߳��е��߳���
	int m_max_requests; //�����������������������
	pthread_t *m_threads; //�����̳߳ص����飬���СΪ m_pthread_number
	std::list<T *> m_wokerqueue;//�������
	locker m_queuelocker;  //����������е���
	sem m_queuestat;	   //�Ƿ���������Ҫ����
	bool m_stop;				//�Ƿ�����߳�
};

#endif