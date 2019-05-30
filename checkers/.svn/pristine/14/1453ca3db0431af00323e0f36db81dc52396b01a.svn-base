#include "Board.h"
#include "BoardTest.h"
#include "Test.h"

void BoardTest::testMakeMove() {
	Board b;
	b.makeMove(3, 6, X);
	b.makeMove(2, 7, O);
	b.makeMove(0, 0, O);
	b.makeMove(9, 9, X);
	DO_CHECK(b.getElement(3,6) == X);
	DO_CHECK(b.getElement(2,7) != X);
	DO_CHECK(b.getElement(0,0) == O);
	DO_CHECK(b.getElement(6,3) == NONE);
}

void BoardTest::testGetState() {
	Board a;
	a.makeMove(1, 1, X);
	a.makeMove(2, 2, X);
	a.makeMove(3, 3, X);
	a.makeMove(4, 4, X);
	a.makeMove(5, 5, X);
	DO_CHECK(a.getState() == X_WON);

	Board b;
	b.makeMove(1, 1, O);
	b.makeMove(2, 1, O);
	b.makeMove(3, 1, O);
	b.makeMove(4, 1, O);
	b.makeMove(5, 1, O);
	DO_CHECK(b.getState() == O_WON);

	Board c;
	c.makeMove(1, 1, X);
	c.makeMove(1, 2, X);
	c.makeMove(1, 3, X);
	c.makeMove(1, 4, X);
	c.makeMove(1, 5, X);
	DO_CHECK(c.getState() == X_WON); //sdfsdf
	
	Board d;
	d.makeMove(4, 4, O);
	d.makeMove(3, 5, O);
	d.makeMove(5, 3, O);
	d.makeMove(6, 2, O);
	d.makeMove(2, 6, O);
	DO_CHECK(d.getState() == O_WON);

	Board e;
	e.makeMove(1, 1, O);
	e.makeMove(2, 1, O);
	e.makeMove(3, 1, O);
	e.makeMove(4, 1, O);
	e.makeMove(4, 4, O);
	e.makeMove(3, 5, O);
	e.makeMove(5, 3, O);
	e.makeMove(6, 2, O);
	DO_CHECK(e.getState() == INPROGRESS);

}

void BoardTest::testCanMove() {
	Board b;
	b.makeMove(1, 1, X);
	DO_CHECK(b.canMove(1,1) == false);
	b.makeMove(1, 2, X);
	DO_CHECK(b.canMove(9,9) == true);
	b.makeMove(1, 3, X);
	DO_CHECK(b.canMove(13, 5) == false);
	b.makeMove(1, 4, X);
	DO_CHECK(b.canMove(-1, 4) == false);
	b.makeMove(1, 5, X);
	DO_CHECK(b.canMove(5, 5) == false);
}

void BoardTest::runAllTests() {
	testMakeMove();
	testGetState();
	testCanMove();
	showFinalResult();
}