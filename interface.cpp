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

int getUserInput() {
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
			break;
		}
	}
	int move = (value[0] - 'A') * 8 + value[1] - '1';
	std::cout << move << std::endl;

	return move;
}
