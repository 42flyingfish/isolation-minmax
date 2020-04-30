#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include <vector>

void printBoard(const Board board, const std::vector<int> log);

int getUserInput(const Board board);
bool computerStartGame();
bool validMove(const Board board, const int move);


// helpers intended to be called by validMove
// largely broken up so I could read this better
bool validUp(const Board board, const int move);
bool validDown(const Board board, const int move);
bool validRight(const Board board, const int move);
bool validLeft(const Board board, const int move);

#endif
