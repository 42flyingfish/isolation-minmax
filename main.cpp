#include <iostream>
#include "agent.h"
#include "board.h"
#include "interface.h"


int main() {
	Board board{};
	printBoard(board);
	std::cout << "Hello world" << std::endl;
	getAiTurn(board);
	return 0;
}

