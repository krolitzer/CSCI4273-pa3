/**
 * Event Schedular library for scheduling network events.
 * Chris Costello and Austin Longo
 **/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <queue>
#include <ctime>
#include <chrono>
#include <vector>

using namespace std;
/** 
 * Making this global to be accessable by all classes
 * Still looking for a better solution.
 **/
struct EventTime
{
	int eventID;
	chrono::milliseconds execTime;
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
	
	
private:
	int num_events;
	int max_events;
	// map of eventID to function to execute
	// schedule execution with priority queue where
	// the smallest delay has highest priority

	struct FunctionInfo
	{
		void evFunction(void *);
		void* arg;
	};
	
	map<int, FunctionInfo> eventFunctionMap;
	priority_queue<EventTime, vector<EventTime>, CompareEventTime> functionQueue;
};




EventScheduler::EventScheduler(size_t maxEvents) {
	max_events = maxEvents;

	cout << "Scheduler created with max " << max_events << " events." << endl;
}

EventScheduler::~EventScheduler() {
	delete eventFunctionMap;
	delete functionQueue;
}

int 
EventScheduler::eventSchedule(void evFunction(void *), void* arg, int timeout) {
	// Decide if timeout is seconds or milliseconds or something else
	// Internally will handle time as milli seconds.


	cout << "Scheduling the function with timeout " << timeout << endl;

	return 0;
}

void
EventScheduler::eventCancel(int eventID) {
	// remove entry from map and priority queue.
	cout << "Cancelled event " << eventID << endl;
}


