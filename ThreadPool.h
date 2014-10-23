/*********************/
/* This is a basic implementation for a thread pool library
*/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

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
    	size_t m_pool_size;
    	char *msg_content;

    	void initialize_pool( );
};

ThreadPool::ThreadPool( )
{
	m_pool_size = DEFAULT_THREAD_COUNT;

	cout << "ThreadPool created with %d threads." << endl;
}

ThreadPool::ThreadPool(size_t threadCount)
{
	m_pool_size = threadCount;

	cout << "ThreadPool created with %d threads." << endl;
}

ThreadPool::~ThreadPool( )
{
    
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

}