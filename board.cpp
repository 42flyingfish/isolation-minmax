#include "board.h"
#include <iostream>


Board::Board() {
	board = 0;
	computer = 0;
	opponent = 63;
	board.set(computer);
	board.set(opponent);
}
