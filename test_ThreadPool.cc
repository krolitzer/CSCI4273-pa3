#include "ThreadPool.h"

int main(int argc, char* argv[])
{
	ThreadPool pool1 = ThreadPool();
	ThreadPool pool2 = ThreadPool(50);
	ThreadPool th(3);

	cout << "Available Threads? " << pool1.thread_avail() << endl;
	cout << "Available Threads? " << pool2.thread_avail() << endl;
	cout << "Available Threads? " << th.thread_avail() << endl;
}