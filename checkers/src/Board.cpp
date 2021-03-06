#include "Board.h"
#include <algorithm>
#include <iostream>

Board::Board() {
	state = INPROGRESS;
	board = new FIGURE*[10];
	for (int i = 0; i < 10; i++) {
		board[i] = new FIGURE[10];
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = NONE;
		}
	}
}

Board::~Board() {
	for (int i = 0; i < 10; i++) {
		delete [] board[i];
	}
	delete [] board;
}

void Board::makeMove(int x, int y, FIGURE f) {
	board[y][x] = f;

	STATE possible_state;
	if (f == X) {
		possible_state = X_WON;
	} else {
		possible_state = O_WON;
	}
	
	int max_consecutive = 0;
	int l, r;

	l = - (std::min(std::min(x, y), 4));      //check diagonal "\"
	r = (std::min(std::min(9 - x, 9 - y), 4));
	for (int i = l; i <= r; i++) {
		if (board[y + i][x + i] == f) {
			max_consecutive++;
		} else {
			max_consecutive = 0;
		}
		if (max_consecutive >= 5) {
			state = possible_state;
		}
	}
	max_consecutive = 0;

	l = - (std::min(std::min(x, 9 - y), 4));      //check diagonal "/"
	r = (std::min(std::min(9 - x, y), 4));
	for (int i = l; i <= r; i++) {
		if (board[y-i][x+i] == f) {
			max_consecutive++;
		} else {
			max_consecutive = 0;
		}
		if (max_consecutive >= 5) {
			state = possible_state;
		}
	}
	max_consecutive = 0;

	l = - (std::min(x, 4));      //check horizontal line
	r = std::min(9-x, 4);
	for (int i = l; i <= r; i++) {
		if (board[y][x+i] == f) {
			max_consecutive++;
		} else {
			max_consecutive = 0;
		}
		if (max_consecutive >= 5) {
			state = possible_state;
		}
	}
	max_consecutive = 0;

	l = - (std::min(y, 4));      //check vertical line
	r = std::min(9-y, 4);
	for (int i = l; i <= r; i++) {
		if (board[y+i][x] == f) {
			max_consecutive++;
		} else {
			max_consecutive = 0;
		}
		if (max_consecutive >= 5) {
			state = possible_state;
		}
	}
	max_consecutive = 0;

	bool isFull = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == NONE) {
				isFull = false;
				break;
			}
		}
	}
	if (isFull == true && state == INPROGRESS) {
		state = DRAW;
	}
}

const bool Board::canMove(int x, int y) {
	if (state != INPROGRESS || x >= 10 || y >= 10 || x < 0 || y < 0) {
		return false;
	}
	if (board[y][x] == NONE) {
		return true;
	} else {
		return false;
	}
}

const FIGURE Board::getElement(int x, int y) {
	return board[y][x];
}

const STATE Board::getState() {
	return state;
}