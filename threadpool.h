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
	int m_thread_number; //线程池中的线程数
	int m_max_requests; //请求队列中允许的最大请求数
	pthread_t *m_threads; //描述线程池的数组，其大小为 m_pthread_number
	std::list<T *> m_wokerqueue;//请求队列
	locker m_queuelocker;  //保护请求队列的锁
	sem m_queuestat;	   //是否有任务需要处理
	bool m_stop;				//是否结束线程
};

#endif