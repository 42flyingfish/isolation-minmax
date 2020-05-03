#include <iostream>
#include "agent.h"
#include "weightedOffenA.h"
#include "weightedDefA.h"
#include "bucketAgent.h"
#include "board.h"
#include "interface.h"

void tourn();

int main() {

	tourn();

	return 0;
}

void tourn() {

	std::vector<int> log;
	Board board{};
	Agent nomral{};
	BucketAgent bucket{};
	WeightedOffenA aggro{};
	WeightedDeffA deff{};
	/*


	// Agent vs Aggo
	while (1) {
		int value = nomral.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = aggro.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}

	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\nnormal was x weightedOffenA was o\n";
	board.reset();

	// Aggo vs Agent
	while (1) {
		int value = aggro.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = nomral.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\n weightedOffenA was x normal was o\n";
	board.reset();

	// Deff vs Agent
	while (1) {
		int value = deff.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = nomral.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\n weightedDefA was x normal was o\n";
	board.reset();

	// Agent vs deff
	while (1) {
		int value = deff.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = nomral.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\n normal was x weightedDefA was o\n";
	board.reset();
	*/

		/*
	// deff vs Aggo
	while (1) {
		printBoard(board, log);
		int value = deff.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = aggro.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	std::cout << "THIS IS ODDD" << std::endl;
	printBoard(board, log);
	std::cout << "\n weightedDefA was x weightedOffenA was o\n";
	board.reset();
	*/
		/*

	// aggro vs deff
	while (1) {
		int value = aggro.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = deff.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\n weightedOffenA was x weightedDefA was o\n";
	board.reset();
	*/

	while (1) {
		printBoard(board, log);
		int value = nomral.getAiTurn(board);
		board.moveComputer(value);
		if (board.gameOver()) {
			break;
		}
		board.swapPlayer();
		value = bucket.getAiTurn(board);
		board.moveComputer(value);
		board.swapPlayer();
		if (board.gameOver()) {
			break;
		}
	}
	std::cout << "\nFinal Board\n";
	printBoard(board, log);
	std::cout << "\n nomral was x bucket was o\n";
	board.reset();

}
