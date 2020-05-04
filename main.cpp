#include <iostream>
#include "agent.h"
#include "board.h"
#include "interface.h"

void playerTurn(Board & board);
void computerTurn(Board & board, Agent & computer);

int main() {
	Board board{};
	Agent computer{};

	printBoard(board);
	std::cout << std::endl;

	if (computerStartGame()) 
		computerTurn(board, computer);

	while (1) {

		playerTurn(board);
	

		if (board.gameOver()) {
			break;
		}

		computerTurn(board, computer);

		if (board.gameOver()) {
			break;
		}

	}

	return 0;
}

void playerTurn(Board & board) {
	int value = getUserInput(board);
	std::cout << std::endl;
	board.moveOpponent(value);
	printBoard(board);
}

void computerTurn(Board & board, Agent & computer) {
	int value = computer.getAiTurn(board);
	board.moveComputer(value);
	printBoard(board);
	std::cout << "Computer’s move is: ";
	printMove(value);
	std::cout << std::endl << std::endl;
}
