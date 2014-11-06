CC = g++
CFLAGS = -Wall -Wextra

all: driver1 driver2 driver3

chatClientMake: driver1.cc
	$(CC) $(CFLAGS) -o driver1 driver1.cc -I.

chatCoordinatorMake: driver2
	$(CC) $(CFLAGS) -o driver2 driver2.cc -I.

chatServerMake: driver3.cc
	$(CC) $(CFLAGS) -o driver3 driver3.cc -I.

clean: 
	rm -f driver1 driver2 driver3
