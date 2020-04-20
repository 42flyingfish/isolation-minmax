#include "board.h"
#include <iostream>

Board::Board() {
	board = 0;
	player = 0;
	opponent = 63;
	board.set(player);
	board.set(opponent);
}
