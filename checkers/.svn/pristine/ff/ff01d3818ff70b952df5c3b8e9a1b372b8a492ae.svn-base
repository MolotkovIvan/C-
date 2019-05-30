#ifndef BOARD_H
#define BOARD_H

#include <cstdio>
#include <cstddef>
enum STATE {INPROGRESS, X_WON, O_WON, DRAW};
enum FIGURE {X, O, NONE};

class Board {
public:
  Board();
  ~Board();
  
  void makeMove(int x, int y, FIGURE);
  const bool canMove(int x, int y);
  const FIGURE getElement(int x, int y);  
  const STATE getState();
private:
  STATE state;
  FIGURE** board;
};

#endif
