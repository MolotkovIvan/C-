.PHONY: all clean

CXX=g++
CXXFLAGS=-std=c++98 -Wall -pedantic

all: main

test: board_test

main: src/main.cpp bin/Board.o bin/View.o include/*.h
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/Board.o bin/View.o

board_test: test/test.cpp bin/Board.o bin/BoardTest.o bin/Test.o include/*.h
	$(CXX) $(CXXFLAGS) -o $@ -Iinclude $< bin/Board.o bin/BoardTest.o bin/Test.o

bin/BoardTest.o: test/BoardTest.cpp include/Test.h include/BoardTest.h include/Board.h
	$(CXX) $(CXXFLAGS) -c test/BoardTest.cpp -o bin/BoardTest.o -Iinclude

bin/Test.o: test/Test.cpp include/Test.h
	$(CXX) $(CXXFLAGS) -c test/Test.cpp -o bin/Test.o -Iinclude

bin/Board.o: src/Board.cpp include/Board.h
	$(CXX) $(CXXFLAGS) -c src/Board.cpp -o bin/Board.o -Iinclude

bin/View.o: src/View.cpp include/Board.h include/View.h
	$(CXX) $(CXXFLAGS) -c src/View.cpp -o bin/View.o -Iinclude

clean:
	rm -rf bin/* main board_test

