/*********************/
/* This is a basic implementation for a thread pool library
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <pthread.h>
#include <map>
#include <queue>

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
		// work structure (function and arg pointer)
    	typedef struct
    	{
	    	void (*dispatch_function)(void*);
	    	void* arg;
		} work_t;


    	size_t 							m_PoolSize;			// the number of threads
    	pthread_t* 						m_ThreadPool;		// array of threads
    	map<pthread_t, pthread_mutex_t> m_ThreadMutexes;	// map of thread ID to associated mutex
    	map<pthread_t, bool>			m_ThreadStatus;		// map of thread ID to availibility boolean
	   	queue<work_t>					m_WorkQueue;		// queue that holds pending work

    	void initialize_pool( );	
    	static void* start_thread(void* arg);
    	static void *work_helper(void *func) 
    	{
			return ((ThreadPool*)func)->start_thread();
		}

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
    delete[] m_ThreadPool;
}

int 
ThreadPool::dispatch_thread(void dispatch_function(void*), void *arg)
{
	work_t newWork;

	newWork.dispatch_function = dispatch_function;
	newWork.arg = arg;

	/*int rc; // Used for return code

	for (int i = 0; i < m_PoolSize; i++)
	{
		if (m_ThreadStatus[m_ThreadPool[i]])
		{
			m_ThreadStatus[m_ThreadPool[i]]	= false;

			//rc = pthread_create(&(m_ThreadPool[i]), NULL, dispatch_function, arg);
		}

		if(rc)
		{
	    	printf("ERROR: return code from pthread_create() is %d\n", rc);
	    	m_ThreadStatus[m_ThreadPool[i]]	= true;
	    	exit(EXIT_FAILURE);
		}
	}*/
}

bool
ThreadPool::thread_avail( )
{
	for(int i = 0; i < m_PoolSize; i++)	
	{
		if(m_ThreadStatus[m_ThreadPool[i]])
			return true;
	}

	// No threads were found available
	return false;
}


void
ThreadPool::initialize_pool( )
{
	m_ThreadPool = new pthread_t[m_PoolSize];

	for (int i = 0; i < m_PoolSize; i++)
	{
		// Declare the mutex
		pthread_mutex_t mutex;

		// Initialize each mutex -> unlocked
		if(pthread_mutex_init(&mutex, NULL))
		{
			printf("ERROR: Failed to initialize mutex.\n");
			exit(EXIT_FAILURE);
		}

		// Declare the thread
		pthread_t thread;
		
		// Add the thread to the array
		m_ThreadPool[i] = thread;

		// Add mapping of thread to mutex
		m_ThreadMutexes[thread] = mutex;

		// Add mapping of thread to availability status
		m_ThreadStatus[thread] = true;

		// Create a null work struct
		work_t work;
		work.dispatch_function = ThreadPool::start_thread;
		work.arg = NULL;

		pthread_create(&thread, NULL, work.dispatch_function, work.arg);
	}

}

void*
ThreadPool::start_thread(void* arg)
{
 //while
	//do work

	return NULL;
}