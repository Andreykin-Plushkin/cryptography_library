CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

SOURCES=*.c
OBJECTS=*.o

EXECUTABLE=main


all: build clean
	./$(EXECUTABLE)
	

build:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) $(OBJECTS) -o main 

clean:
	rm -f *.o
