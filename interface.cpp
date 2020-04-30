#include "interface.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <string>

// prints board state
void printBoard(const Board board, const std::vector<int> log) {
	std::cout << "  1 2 3 4 5 6 7 8     Computer vs. Opponent\n";
	for (unsigned int i = 0; i < 8; ++i) {
		std::cout << char('A' + i);
		for (int j = 0; j < 8; ++j) {
			int index = i*8+j;
			if (board.board.test(index)) {
				if (index == board.player) {
					std::cout << ' ' << 'X';
				} else if (index == board.opponent) {
					std::cout << ' ' << 'O';
				} else {
					std::cout << ' ' << '#';
				}
			} else {
				std::cout << ' ' << '_';
			}
		}
		if (log.size() >= 2*i+1) {
			std::cout << " True" << std::endl;
		} else {
			std::cout << "        " << std::endl;
		}
	}
}

int getUserInput(const Board board) {
	std::string value;
	while (1) {
		std::cout << "Enter opponent’s move: ";
		if(!std::getline(std::cin, value)) {
			std::cout << "Somehow an io error occured. Let's try that again\n";
		}
		if (value.length() != 2) {
			std::cout << "Please enter a string of length 2\n";
		} else if (value[0] < 'A' || value[0] > 'H') {
			std::cout << "Must start with a capital letter between A and H inclusive\n";
		} else if (value[1] < '1' || value[1] > '8') {
			std::cout << "Must end with a digit between 1 and 8 inclusive\n";
		} else {
			int move = (value[0] - 'A') * 8 + value[1] - '1';
			//if (validMove(board, move)) {
				return move;
			//}
		}
	}
}

bool computerStartGame() {
	std::string value;
	while (1) {
		std::cout << "Who should start? Computer or Opponent (C/O): ";
		if(!std::getline(std::cin, value)) {
			std::cout << "Somehow an io error occured. Let's try that again\n";
		}
		if (value == "C") {
			return true;
		} else if (value == "O") {
			return false;
		} else {
			std::cout << "Input must be C or O\n";
		}
	}

	return false;
}

bool validMove(const Board board, const int move) {
	// space is occuppied
	if (board.board.test(move)) {
		return false;
		// check if in same collum
	} else if (board.opponent % 8 == move % 8) {
		if (board.opponent > move) {
			return validUp(board, move);
		} else {
			return validDown(board, move);
		}
	} else if (board.opponent / 8 == move / 8) {
		if (board.opponent > move) {
			return validLeft(board, move);
		} else {
			return validRight(board, move);
		}
	}
	// check diagonals
	else {

		return true;
	}
}

// check if move is valid upwards
bool validUp(const Board board, const int move) {
	if (move % 8 != board.opponent % 8 || move > board.opponent) {
		return false;
	}
	for (int i = move + 8; i < board.opponent; i++) {
		if (board.board.test(i)) {
			return false;
		}
	}
	return true;
}

// check if new move is below 
bool validDown(const Board board, const int move) { 
	if (move % 8 != board.opponent % 8 || move < board.opponent) {
		return false;
	}
	for (int i = move - 8; i > board.opponent; --i) {
		if (board.board.test(i)) {
			return false;
		}
	}
	return true;
}

bool validLeft(const Board board, const int move) {
	if (move / 8 != board.opponent / 8 || move > board.opponent) {
		return false;
	}
	for (int i = move + 1; i < board.opponent; ++i) {
		if (board.board.test(i)) {
			return false;
		}
	}
	return true;
}

bool validRight(const Board board, const int move) {
	if (move / 8 != board.opponent / 8 || move < board.opponent) {
		return false;
	}
	for (int i = move -1; i > board.opponent; --i) {
		if (board.board.test(i)) {
			return false;
		}
	}
	return true;
}
