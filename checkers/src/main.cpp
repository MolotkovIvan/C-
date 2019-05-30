#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include "Board.h"
#include "View.h"

int main(int argc, char* argv[]) {
	Board *b = new Board();
	View *v = new View(b);
	if (argc == 2 && strcmp(argv[1], "silent") == 0) {
		v->startGame(true);
	} else {
		v->startGame(false);
	}
	delete b;
	delete v;
}