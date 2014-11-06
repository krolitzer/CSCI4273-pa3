#This makefile is jacked up and I haven't figured out how to make it work.
#It keeps ignoring the ccflags argument.
#compile with -> g++ -Wall -Wextra -std=gnu++11 driver2.cc -o driver2

CC = g++
CCFLAGS = -Wall -Wextra -std=gnu++11

all: driver1 driver2 driver3

driver1Make: driver1.cc
	$(CC) $(CCFLAGS) -o driver1 driver1.cc -I.

driver2Make: driver2
	$(CC) $(CCFLAGS) -o driver2 driver2.cc -I.

driver3Make: driver3.cc
	$(CC) $(CCFLAGS) -o driver3 driver3.cc -I.

clean: 
	rm -f driver1 driver2 driver3
