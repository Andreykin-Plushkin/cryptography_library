CC=gcc
CFLAGS=-c -Wall -Wextra -Werror

SOURCES=*.c
OBJECTS=*.o

EXECUTABLE=main


all: clean build
	./$(EXECUTABLE)
	
git: clean
	git add .
	git commit
	git push

build:
	$(CC) $(CFLAGS) $(SOURCES)
	$(CC) $(OBJECTS) -o main 

clean:
	rm -f *.o $(EXECUTABLE)
