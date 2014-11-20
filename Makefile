#This makefile is jacked up and I haven't figured out how to make it work.
#It keeps ignoring the ccflags argument.
#compile with -> g++ -Wall -Wextra -std=gnu++11 driver2.cc -o driver2

CC = g++
CCFLAGS = -std=gnu++11 -pthread -g

all: driver1Make driver2Make driver3Make driver3ModMake threadPoolMake messageMake eventSchedulerMake

driver1Make: driver1.cc
	$(CC) $(CCFLAGS) -o driver1 driver1.cc -I.

driver2Make: driver2.cc
	$(CC) $(CCFLAGS) -o driver2 driver2.cc -I.

driver3Make: driver3.cc
	$(CC) $(CCFLAGS) -o driver3 driver3.cc -I.

driver3ModMake: driver3_modified.cc
	$(CC) $(CCFLAGS) -o driver3_modified driver3_modified.cc -I.

threadPoolMake: ThreadPool.h
	$(CC) $(CCFLAGS) -o ThreadPool ThreadPool.h

messageMake: Message.h
	$(CC) $(CCFLAGS) -o Message Message.h 

eventSchedulerMake: EventScheduler.h
	$(CC) $(CCFLAGS) -o EventScheduler EventScheduler.h

clean: 
	rm -f driver1 driver2 driver3 driver3_modified ThreadPool Message EventScheduler
