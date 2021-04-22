#ifndef INTERFACE_H
#define INTERFACE_H

#include "board.h"
#include "log.h"

void printBoard(const Board board, const Log log);
void printMove(const int);

int getUserInput(const Board board);
bool computerStartGame();

#endif
