#include "interface.h"
#include "board.h"
#include <iostream>
#include <vector>
#include <string>

// prints board state
void printBoard(const Board board) {

	std::vector<int> computerLog = board.getCLog();
	std::vector<int> opponentLog = board.getOLog();

	auto cit = computerLog.begin();
	auto oit = opponentLog.begin();


	std::cout << "  1 2 3 4 5 6 7 8     Computer vs. Opponent\n";
	for (unsigned int i = 0; i < 8; ++i) {
		std::cout << char('A' + i);
		for (int j = 0; j < 8; ++j) {
			int index = i*8+j;
			if (board.test(index)) {
				if (index == board.getComputer()) {
					std::cout << ' ' << 'X';
				} else if (index == board.getOpponent()) {
					std::cout << ' ' << 'O';
				} else {
					std::cout << ' ' << '#';
				}
			} else {
				std::cout << ' ' << '-';
			}
		}

		// printing the log
		//
		// check if log is not empty
		if (cit != computerLog.end() || cit != opponentLog.end()) {

			// print number
			std::cout << "        " << i << ". ";

			if (cit != computerLog.end()) {
				printMove(*cit);
				cit++;
			} else {
				std::cout << "  ";
			}

			// spacer
			std::cout << "   ";

			if (oit != opponentLog.end()) {
				printMove(*oit);
				oit++;
			}
		}
		std::cout << std::endl;

	}
	// check if log is not empty
	for (int i = 9; cit != computerLog.end() || oit != opponentLog.end(); ++i) {

		// print number
		std::cout << "                         " << i << ". ";

		if (cit != computerLog.end()) {
			printMove(*cit);
			cit++;
		} else {
			std::cout << "  ";
		}

		// spacer
		std::cout << "   ";

		if (oit != opponentLog.end()) {
			printMove(*oit);
			oit++;
		}

		std::cout << std::endl;

	}
	std::cout << "\n\n";
}




void printMove(const int move) {
	char letter = 'A' + move / 8;

	// Plus one is needed due to moves starting at 0
	int num = move % 8 + 1;

	std::cout << letter << num;


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
	if (board.test(move)) {
		return false;
		// check if in same collum
	} else if (board.getOpponent() % 8 == move % 8) {
		if (board.getOpponent() > move) {
			return validUp(board, move);
		} else {
			return validDown(board, move);
		}
	} else if (board.getOpponent() / 8 == move / 8) {
		if (board.getOpponent() > move) {
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
	if (move % 8 != board.getOpponent() % 8 || move > board.getOpponent()) {
		return false;
	}
	for (int i = move + 8; i < board.getOpponent(); i++) {
		if (board.test(i)) {
			return false;
		}
	}
	return true;
}

// check if new move is below 
bool validDown(const Board board, const int move) { 
	if (move % 8 != board.getOpponent() % 8 || move < board.getOpponent()) {
		return false;
	}
	for (int i = move - 8; i > board.getOpponent(); --i) {
		if (board.test(i)) {
			return false;
		}
	}
	return true;
}

bool validLeft(const Board board, const int move) {
	if (move / 8 != board.getOpponent() / 8 || move > board.getOpponent()) {
		return false;
	}
	for (int i = move + 1; i < board.getOpponent(); ++i) {
		if (board.test(i)) {
			return false;
		}
	}
	return true;
}

bool validRight(const Board board, const int move) {
	if (move / 8 != board.getOpponent() / 8 || move < board.getOpponent()) {
		return false;
	}
	for (int i = move -1; i > board.getOpponent(); --i) {
		if (board.test(i)) {
			return false;
		}
	}
	return true;
}
