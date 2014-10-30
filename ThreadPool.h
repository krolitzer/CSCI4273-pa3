/*********************/
/* This is a basic implementation for a thread pool library
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
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
    	int* m_ThreadStatus;


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
    delete m_ThreadStatus;
}

int 
ThreadPool::dispatch_thread(void dispatch_function(void*), void *arg)
{
	if(thread_avail())
	{
		int rc; // Used for return code

		// m_ThreadStatus[i] = 1;
		//rc = pthread_create(&(m_ThreadPool[i]), NULL, dispatch_function, arg);
		if(rc){
		    printf("ERROR; return code from pthread_create() is %d\n", rc);
		    exit(EXIT_FAILURE);
		}
		// m_ThreadStatus[i] = 0;
	}
}

bool
ThreadPool::thread_avail( )
{
	for(int i = 0; i < m_PoolSize; i++)	
	{
		if(m_ThreadStatus[i] == 0)
			return true;
	}

	// No threads were found available
	return false;
}


void
ThreadPool::initialize_pool( )
{
	m_ThreadPool = new pthread_t[m_PoolSize];
	m_ThreadStatus = new int[m_PoolSize];
}

void
ThreadPool::free_thread( )
{

}