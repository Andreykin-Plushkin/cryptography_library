CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

SOURCES=sources/*.c
OBJECTS=*.o

EXECUTABLE=main


all: clean build
	./$(EXECUTABLE)
	
git: clean
	git add .
	git commit
	git push

build:
	$(CC) $(CFLAGS) lib.c $(EXECUTABLE).c $(SOURCES)
	$(CC) $(OBJECTS) -o $(EXECUTABLE) 

clean:
	rm -f *.o $(EXECUTABLE)
