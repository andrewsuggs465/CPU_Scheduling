CC = gcc
CFLAGS = -Wall -Wextra -g

scheduler : main.o parser.o
	$(CC) $(CFLAGS) -o scheduler main.o parser.o

main.o : main.c parser.h
	$(CC) $(CFLAGS) -c main.c

parser.o : parser.c parser.h
	$(CC) $(CFLAGS) -c parser.c

.PHONY : clean
clean:
	rm -f scheduler *.o