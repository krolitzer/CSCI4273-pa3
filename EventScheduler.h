/**
 * Event Schedular library for scheduling network events.
 * Chris Costello and Austin Longo
 **/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <queue>
#include <ctime>
#include <chrono>
#include <vector>
#include <pthread.h>
#include "ThreadPool.h"

using namespace std;
/** 
 * Making this global to be accessable by all classes
 * Still looking for a better solution.
 **/
struct EventTime
{
	int eventID;
	long execTime;
};
	
/** Making new class for priority queue compatability */
class CompareEventTime {
public:
	/**
	 * Used by priority queue to order based on exec time.
	 * Orders earliest first.
	 **/
	bool operator()(EventTime &e1, EventTime &e2) {
		if (e2.execTime < e1.execTime) {
			return true;
		}
		return false;
	}
};

class EventScheduler {
public:
	EventScheduler(size_t maxEvents);
	~EventScheduler();
	int eventSchedule(void evFunction(void *), void* arg, int timeout);
	void eventCancel(int eventID);
	void printQ();
	void dumpQ();
	
private:
	int num_events;
	int max_events;
	int event_num;
	// map of eventID to function to execute
	// schedule execution with priority queue where
	// the smallest delay has highest priority

	struct FunctionInfo
	{
		void (*function)(void*);
		void* arg;
	};
	
	typedef map<int, FunctionInfo> eventFunctionMap;
	typedef priority_queue<EventTime, vector<EventTime>, CompareEventTime> functionQueue;
	eventFunctionMap efMap;
	functionQueue fQueue;
	
	pthread_t thread;
	pthread_mutex_t queue_mutex;

	long getExecTime(int timeout);
	void* executeEvents(void);
	long getNow();

	static void *work_helper(void *instance) {
		return ((EventScheduler*)instance)->executeEvents();
	}
	
};




EventScheduler::EventScheduler(size_t maxEvents) {
	max_events = maxEvents;
	event_num = 0;
	pthread_mutex_init(&queue_mutex, NULL);
	pthread_create(&thread, NULL, work_helper, this);
	cout << "EventScheduler created with max " << max_events << " events." << endl;
}

EventScheduler::~EventScheduler() {
	while(!fQueue.empty()) {}
	pthread_join(thread, NULL);
	
}

int 
EventScheduler::eventSchedule(void evFunction(void *), void* arg, int timeout) {
	// Decide if timeout is seconds or milliseconds or something else
	// Internally will handle time as milli seconds.
	int thisEvent = event_num;
	// Record the function to call plus the arg
	FunctionInfo f; 
	f.function = evFunction;
	f.arg = arg;

	// Record the eventID with the time to execute.
	EventTime e;
	e.eventID = thisEvent;
	e.execTime = getExecTime(timeout);

	if( pthread_mutex_lock(&queue_mutex) ) {
		fprintf(stderr, "A mutex error occurred");
	}
	// Store info in map
	efMap.insert(eventFunctionMap::value_type(thisEvent, f));
	// Schedule in priority queue
	fQueue.push(e);
	pthread_mutex_unlock(&queue_mutex);

	cout << "Scheduled function with timeout " << timeout << " event id = " << event_num << endl;

	event_num++;
	return thisEvent;
}

void
EventScheduler::eventCancel(int eventID) {
	/* This will not remove events from the queue.
	   When the eventID is not found in the map,
	   that item will simply get popped and the 
	   event executer will move on. */
	
	// Remove entry from map
	efMap.erase(eventID);
	cout << "Cancelled event " << eventID << endl;
}

long
EventScheduler::getExecTime(int timeout) {
	// NOTE: Assuming timeout is in milliseconds.
	using namespace std::chrono;

	long now = getNow();

	long execTime = now + milliseconds(timeout).count();

	// cout << "Event scheduled with time " << now.count() << " and execution time " << execTime.count() << endl
	// << "Will execute in " << (execTime-now).count() << endl;

	return execTime;
}

long
EventScheduler::getNow() {
	using namespace std::chrono;
	return duration_cast<milliseconds>(
		high_resolution_clock::now().time_since_epoch()).count();
}

void *
EventScheduler::executeEvents(void) {
	// A seperate thread is running this function
	// Check the queue and run functions when the time is up.
	// Note, if eventID is not found in the map, 
	// Then it must have been cancelled, so move on.

	cout << "Thread to start executing stuff!!" << endl;
	ThreadPool tp(max_events);
	// Look into pthread_conditional thing.
	while(true) {
		long countDown = 100;

		if(!fQueue.empty()) {
			countDown = fQueue.top().execTime - getNow();
		} 		
		
		if(countDown <= 0) {
			
			// grab function information from the map
			int id = fQueue.top().eventID;
			eventFunctionMap::iterator it = efMap.find(id);
			
			if(it == efMap.end()) {
				//didn't find the element
				cout << "Event confirmed cancelled" << endl;
				fQueue.pop();
				efMap.erase(id);
			} else {
				// execute the function, tp handles thread availability
				tp.dispatch_thread(it->second.function, it->second.arg);
				cout << "Dispached thead for event " << id << endl;
				fQueue.pop();
				efMap.erase(id);
			}
		}
		// Still trying to find a reasonable amount of time to sleep
		usleep(countDown/2);
	}
	return NULL;
}

void
EventScheduler::dumpQ() {
	cout << "-------------------Queue Dump-----------" << endl;

	while(!fQueue.empty()) {
		cout << fQueue.top().execTime << "  " << fQueue.top().eventID << endl;
		fQueue.pop();
	}

	cout << "---------------End Queue Dump-----------" << endl;
}

void
printMap() {
	
}
