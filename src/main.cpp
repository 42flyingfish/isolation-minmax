#include <iostream>
#include "agent.h"
#include "board.h"
#include "log.h"
#include "interface.h"

void playerTurn(Board & board, Log & log);
void computerTurn(Board & board, Agent & computer, Log & log);

int main() {
	Board board{};
	Agent computer{};
	Log log{};

	printBoard(board, log);
	std::cout << std::endl;

	if (computerStartGame()) 
		computerTurn(board, computer, log);

	while (1) {

		playerTurn(board, log);
	

		if (board.gameOver()) {
			break;
		}

		computerTurn(board, computer, log);

		if (board.gameOver()) {
			break;
		}

	}

	return 0;
}

void playerTurn(Board & board, Log & log) {
	int value = getUserInput(board);
	std::cout << std::endl;
	board.moveOpponent(value);
	log.recordOpponent(value);
	printBoard(board, log);
}

void computerTurn(Board & board, Agent & computer, Log & log) {
	int value = computer.getAiTurn(board);
	board.moveComputer(value);
	log.recordComputer(value);
	printBoard(board, log);
	std::cout << "Computer’s move is: ";
	printMove(value);
	std::cout << std::endl << std::endl;
}
