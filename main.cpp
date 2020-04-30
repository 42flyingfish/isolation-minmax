#include <iostream>
#include "agent.h"
#include "board.h"
#include "interface.h"

int main() {
	std::vector<int> log;
	Board board{};

	/*
	if (computerStartGame()) {
		int value = getAiTurn(board);
		std::cout << value << '\n';
		board.moveComputer(value);
		printBoard(board, log);
	}
	*/

	while (1) {
	
		int value = getAiTurn(board);
		board.moveComputer(value);

		printBoard(board, log);
	

		if (board.gameOver()) {
			break;
		}

		board.swapPlayer();


		value = getAiTurn(board);
		board.moveComputer(value);

		board.swapPlayer();
		printBoard(board, log);
	

		if (board.gameOver()) {
			break;
		}

	}

	std::cout << "\nFinal Board\n";
	
	printBoard(board, log);
	
	return 0;
}
