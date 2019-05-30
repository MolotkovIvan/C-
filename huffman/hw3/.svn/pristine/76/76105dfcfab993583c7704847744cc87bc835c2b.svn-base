.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g

all: main

main: src/main.cpp include/huffman.h
	$(CXX) $(CXXFLAGS) src/main.cpp -o $@ -Iinclude


clean:
	rm -rf bin main
