# Makefile
# COMP 3500 Project 5 - CPU Scheduling
# Author: Andrew Suggs (ads0127@auburn.edu)
#
# Separate compilation of the scheduler. "make" builds ./scheduler,
# "make clean" removes the object files and the binary.

CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o parser.o scheduler.o

scheduler : $(OBJS)
	$(CC) $(CFLAGS) -o scheduler $(OBJS)

main.o : main.c parser.h scheduler.h
	$(CC) $(CFLAGS) -c main.c

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

scheduler.o : scheduler.c scheduler.h parser.h
	$(CC) $(CFLAGS) -c scheduler.c

.PHONY : clean
clean :
	rm -f scheduler $(OBJS)
