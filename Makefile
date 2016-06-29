CC=g++
CFLAGS=-std=c++11

test: test.cpp ConfigParser.cpp ConfigParser.h
	$(CC) -o test test.cpp ConfigParser.cpp $(CFLAGS) -I.

clean:
	rm test
