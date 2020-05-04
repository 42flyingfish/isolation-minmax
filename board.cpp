#include "board.h"
#include <string>
#include <iostream>
#include "interface.h"
#include <vector>


Board::Board() {
	computer = 0;
	opponent = 63;
	board.set(computer);
	board.set(opponent);
}

Board::Board(const int x, const int y) : computer{x}, opponent{y} {
	board = 0;
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

bool Board::gameOver() const {
	return !canMoveFrom(computer) || !canMoveFrom(opponent);
}

int Board::getComputer() const {
	return computer;
}

int Board::getOpponent() const {
	return opponent;
}

bool Board::canMoveFrom(const int pos) const {
	// check up
	int nextPos = pos - 8;
	if (nextPos >= 0 && !board.test(nextPos)) {
		//std::cout << "Good up\n";
		return true;
	}
	
	// check down
	nextPos = pos + 8;
	if (nextPos < 64 && !board.test(nextPos))
		return true;

	// check left
	nextPos = pos - 1;
	if (nextPos >= 0 && nextPos%8 < pos%8 && !board.test(nextPos))
		return true;

	// check right
	nextPos = pos + 1;
	if (nextPos < 64 && nextPos%8 > pos%8 && !board.test(nextPos))
		return true;
	
	// check up left
	nextPos = pos - 1 - 8;
	if (nextPos >= 0 && nextPos%8 < pos%8 && !board.test(nextPos))
		return true;

	// check up right
	nextPos = pos + 1 - 8;
	if (nextPos >= 0 && nextPos%8 > pos%8 && !board.test(nextPos))
		return true;
	
	// check down left
	nextPos = pos - 1 + 8;
	if (nextPos < 64 && nextPos%8 < pos%8 && !board.test(nextPos))
		return true;
	
	// check down right
	nextPos = pos + 1 + 8;
	if (nextPos < 64 && nextPos%8 > pos%8 && !board.test(nextPos))
		return true;

	return false;
}

void Board::swapPlayer() {
	int temp = computer;
	computer = opponent;
	opponent = temp;
}

void Board::reset() {
	board = 0;
	computer = 0;
	opponent = 63;
	board.set(computer);
	board.set(opponent);
}

std::bitset<64> Board::getBitset() const {
	return board;
}
