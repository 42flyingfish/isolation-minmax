#include <iostream>
#include "agent.h"
#include "board.h"
#include "interface.h"

void tourn();

int main() {
	Board board{};
	std::vector<int> logComputer;
	std::vector<int> logBlayer;
	printBoard(board, logComputer);
	if (board.gameOver()) {
		std::cout << "Yes" << std::endl;
	}

	tourn();

	return 0;
}

void tourn() {

}
