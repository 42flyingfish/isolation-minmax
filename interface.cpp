#include "interface.h"
#include "board.h"
#include <iostream>

void printBoard(const Board board) {
	std::cout << "  1 2 3 4 5 6 7 8     Computer vs. Opponent\n";
	for (int i = 0; i < 8; ++i) {
		std::cout << char('A' + i);
		for (int j = 0; j < 8; ++j) {
			std::cout << ' ' << board.board[i*8+j];
		}
		std::cout << std::endl;

	}
}
