CC = g++
CFLAGS = -O3 -std=c++11 -Wall

all: maxcut

maxcut: src/maxcut.cpp
	$(CC) $(CFLAGS) src/maxcut.cpp -o maxcut

clean:
	rm -f maxcut