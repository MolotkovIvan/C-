.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++98 -Wall -pedantic

all: main

main: src/main.cpp include/my_vector.h
	$(CXX) $(CXXFLAGS) src/main.cpp -o $@ -Iinclude


clean:
	rm -rf bin main
