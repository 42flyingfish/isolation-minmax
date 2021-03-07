#include "board.h"
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
	computerLog.push_back(value);
}

void Board::moveComputerNoLogging(const int value) {
	board.set(value);
	computer = value;
}

void Board::moveOpponent(const int value) {
	board.set(value);
	opponent = value;
	opponentLog.push_back(value);
}

void Board::moveOpponentNoLogging(const int value) {
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

std::vector<int> Board::expandComp() const {
	std::vector<int> children {};

	// move down right
	for (int i = 9 + getComputer(); i%8 > getComputer()%8 && i < 64; i+=9) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up left
	for (int i = -9 + getComputer(); i%8 < getComputer() %8 && i > 0; i-=9) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move down left
	for (int i = 7 + getComputer(); i%8 < getComputer() %8  && i < 64; i+=7) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up right
	for (int i = -7 + getComputer(); i%8 > getComputer()%8 && i > 0; i-=7) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move down
	for (int i = 8 + getComputer(); i < 64; i+=8) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up
	for (int i = -8 + getComputer(); i > 0; i-=8) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}


	// move left
	for (int i = getComputer() -1; i%8 < 7 && i > 0; --i) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}


	// move right
	for (int i = getComputer() +1; i%8 > 0; ++i) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	return children;

}

std::vector<int> Board::expandOpp() const {
	std::vector<int> children {};

	// move down right
	for (int i = 9 + getOpponent(); i%8 > getOpponent()%8 && i < 64; i+=9) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up left
	for (int i = -9 + getOpponent(); i%8 < getOpponent() %8 && i > 0; i-=9) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move down left
	for (int i = 7 + getOpponent(); i%8 < getOpponent() %8  && i < 64; i+=7) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up right
	for (int i = -7 + getOpponent(); i%8 > getOpponent()%8 && i > 0; i-=7) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move down
	for (int i = 8 + getOpponent(); i < 64; i+=8) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	// move up
	for (int i = -8 + getOpponent(); i > 0; i-=8) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}


	// move left
	for (int i = getOpponent() -1; i%8 < 7 && i > 0; --i) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}


	// move right
	for (int i = getOpponent() +1; i%8 > 0; ++i) {
		if(board.test(i)) {
			break;
		}
		children.push_back(i);
	}

	return children;

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

std::vector<int> Board::getCLog() const {
	return computerLog;
}

std::vector<int> Board::getOLog() const {
	return opponentLog;
}
