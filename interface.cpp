#include "interface.h"
#include "board.h"
#include <iostream>

void printBoard(const Board board) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board.board[i*8+j]) {
				std::cout << 'X' << ' ';
			} else {
				std::cout << (i*8+j) << ' ';
			}
		}
		std::cout << "\n";
	}
}
