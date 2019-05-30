#ifndef VIEW_H
#define VIEW_H

#include <cstdio>
#include <cstddef>
#include "Board.h"
class View {
public:
  View(Board *b);
  
  const void showBoard();
  const void startGame(bool silent);
private:
  Board *board;
};

#endif
