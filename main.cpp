#include <iostream>
#include "minMax.h"
#include "board.h"

void printBoard(const Board board);

int main() {
	Board board{};
	printBoard(board);
	std::cout << "Hello world" << std::endl;
	getAiTurn(board);
	return 0;
}

void printBoard(const Board board) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (board.board[i*8+j]) {
				std::cout << 'X' << ' ';
			} else {
				std::cout << 0 << ' ';
			}
		}
		std::cout << "\n";
	}
}
