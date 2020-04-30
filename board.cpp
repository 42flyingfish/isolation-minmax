#include "board.h"


Board::Board() {
	board = 0;
	computer = 0;
	opponent = 63;
	board.set(computer);
	board.set(opponent);
}

void Board::moveComputer(const int value) {
	board.set(value);
	computer = value;
}

void Board::moveOpponent(const int value) {
	board.set(value);
	opponent = value;
}

bool Board::test(const size_t pos) const {
	return board.test(pos);
}

int Board::getComputer() const {
	return computer;
}

int Board::getOpponent() const {
	return opponent;
}
