#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"

void printBoard(const Board board);
void printMove(const int);

int getUserInput(const Board board);
bool computerStartGame();


#endif
