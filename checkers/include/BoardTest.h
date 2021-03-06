#ifndef BOARDTEST_H
#define BOARDTEST_H

#include <cstdio>
#include <cstddef>
#include "Board.h"
#include "Test.h"

class BoardTest: Test {
public:
	void testMakeMove();
	void testCanMove();
	void testGetElement();
	void testGetState();
	void runAllTests();
};

#endif