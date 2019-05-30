#include <iostream>
#include <string>
#include "View.h"
#include "Board.h"

View::View(Board *b) {
	board = b;
}

const void View::showBoard() {
	std::cout << "\n";
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board->getElement(j, i) == X) {
				std::cout << "X";
			} else if (board->getElement(j, i) == O) {
				std::cout << "O";
			} else {
				std::cout << ".";
			}
		}
		std::cout << "\n";
	}
}

const void View::startGame(bool silent) {
	if (!silent) {
		showBoard();
	}
	int x;
	int y;
	while (board->getState() == INPROGRESS) {
		std::cout << "O move: ";
		std::cin >> y >> x;
		if (y == -1 && x == -1) {
			return;
		}
		while (!board->canMove(x, y)) {
			std::cout << "Bad move!\n";
			std::cout << "O move: ";
			std::cin >> y >> x;		
			if (y == -1 && x == -1) {
				return;
			}
		}
		board->makeMove(x, y, O);
		if (!silent) {
			showBoard();
		}

		if (board->getState() != INPROGRESS) {
			break;
		}
		
		std::cout << "X move: ";
		std::cin >> y >> x;
		if (y == -1 && x == -1) {
			return;
		}
		while (!board->canMove(x, y)) {
			std::cout << "Bad move!\n";
			std::cout << "X move: ";
			std::cin >> y >> x;		
			if (y == -1 && x == -1) {
				return;
			}
		}
		board->makeMove(x, y, X);
		if (!silent) {
			showBoard();
		}
	}
	if (silent) {
		showBoard();
	}
	if (board->getState() == X_WON) {
		std::cout << "X wins!\n"; 
	} else if (board->getState() == O_WON) {
		std::cout << "O wins!\n"; 		
	} else {
		std::cout << "Draw.\n"; 		
	}
}