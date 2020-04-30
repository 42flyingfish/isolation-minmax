#include <iostream>
#include "agent.h"
#include "board.h"
#include "interface.h"


int main() {
	std::vector<int> log;
	Board board{};

	if (computerStartGame()) {
		int value = getAiTurn(board);
		std::cout << value << '\n';
		board.moveComputer(value);
		printBoard(board, log);
	}

	while (1) {
		int move = getUserInput(board);
		board.moveOpponent(move);
		int value = getAiTurn(board);
		board.moveComputer(value);
		printBoard(board, log);
	}
	getAiTurn(board);
	return 0;
}

