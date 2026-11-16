CC = gcc
CFLAGS = -Wall -Wextra -g

scheduler : main.o parser.o scheduler.o
	$(CC) $(CFLAGS) -o scheduler main.o parser.o scheduler.o

main.o : main.c parser.h scheduler.h
	$(CC) $(CFLAGS) -c main.c

scheduler.o : scheduler.h scheduler.h
	$(CC) $(CFLAGS) -c scheduler.c

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

.PHONY : clean
clean:
	rm -f scheduler *.o