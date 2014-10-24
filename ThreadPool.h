/*********************/
/* This is a basic implementation for a thread pool library
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <pthread.h>

#define DEFAULT_THREAD_COUNT 10

using namespace std;

class ThreadPool
{
	public:
		ThreadPool( );
	    ThreadPool(size_t threadCount);
	    ~ThreadPool( );
	    int dispatch_thread(void dispatch_function(void*), void *arg);
	    bool thread_avail( );

	private:
    	size_t m_PoolSize;
    	pthread_t* m_ThreadPool;


    	//Thread struct

    	void initialize_pool( );
    	void free_thread( /*pointer to thread struct*/);
};

ThreadPool::ThreadPool( )
	:m_PoolSize(DEFAULT_THREAD_COUNT)
{
	initialize_pool();
	cout << "ThreadPool created with " << m_PoolSize << " threads." << endl;
}

ThreadPool::ThreadPool(size_t threadCount)
	:m_PoolSize(threadCount)
{
	initialize_pool();
	cout << "ThreadPool created with " << m_PoolSize << " threads." << endl;
}

ThreadPool::~ThreadPool( )
{
    delete m_ThreadPool;
}

int 
ThreadPool::dispatch_thread(void dispatch_function(void*), void *arg)
{

}

bool
ThreadPool::thread_avail( )
{

}


void
ThreadPool::initialize_pool( )
{
	m_ThreadPool = new pthread_t[m_PoolSize];
}

void
ThreadPool::free_thread( )
{

}