/**
 * Event Schedular library for scheduling network events.
 * Chris Costello and Austin Longo
 **/

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <map>

using namespace std;

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

	struct functionInfo
	{
		void evFunction(void *);
		void* arg;
	};

	map<int, functionInfo> eventFunctionMap;
	
}

EventScheduler::EventScheduler(size_t maxEvents) {
	max_events = maxEvents;

	cout << "Scheduler created with max " + max_events " events." << endl;
}

EventScheduler::~EventScheduler() {
	// delete data structures
}

int 
EventScheduler::eventSchedule(void evFunction(void *), void* arg, int timeout) {
	cout << "Scheduling the function with timeout" << endl;
	return 0;
}

void
eventCancel(int eventID) {
	cout << "Cancelled event " + event << endl;
}



