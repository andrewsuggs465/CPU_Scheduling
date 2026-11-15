CC = gcc
CFLAGS = -Wall -Wextra -g

scheduler : scheduler.o parser.o
	$(CC) $(CFLAGS) -o scheduler scheduler.o parser.o

scheduler.o : scheduler.c parser.h
	$(CC) $(CFLAGS) -c scheduler.c

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

.PHONY : clean
clean:
	rm -f scheduler *.o