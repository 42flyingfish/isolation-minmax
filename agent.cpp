#include "agent.h"
#include "board.h"
#include "interface.h"

#include <atomic> // for std::atomic<bool> 
#include <chrono> // for std::chrono::seconds
#include <condition_variable> // for cv.wait_for
#include <iostream>
#include <mutex> // used with std::condition_variable
#include <thread> // to run the timeout and minMax function in threads
#include <limits> // to init alpha/beta small/big number

// returns a value to move
void getAiTurn(const Board board) {
	std::cout << "Hello\n";
	wrapper(board);
	std::cout << "Done\n";
}

// A wrapper built around the minmax algorithm
// Will set an atomic boolean flag to true after the alloted time has expired
// Also accepts an early notification through the condition_variable
//    so that it does not always take the full alloted time
void wrapper(const Board board) {
	std::mutex m, critical;
	std::condition_variable cv;
	std::atomic<bool> flag {false};

	std::thread third(minMax, std::ref(cv), std::ref(flag), board, std::ref(critical));
	third.detach();

	std::unique_lock<std::mutex> l{m};
	if (cv.wait_for(l, std::chrono::seconds(20)) == std::cv_status::timeout) {

		// set timeout flag to be read by thread
		flag = true;
		std::cout << "Tick tock!\n";
		// waiting for minMax to finish
		critical.lock();
		critical.unlock();
	} else {
		std::cout << "Algorithm returned Early\n";
	}
	return;
}


void minMax(std::condition_variable & cv, std::atomic<bool> & flag, Board board, std::mutex & critical) {

	critical.lock();

	// init alpha beta
	int alpha{std::numeric_limits<int>::min()};
	int beta{std::numeric_limits<int>::max()};

	for (int i=0; i <= 0; ++i) {
		if (flag) {
			std::cout << i << "Exiting loop\n";
			break;
		}
		try {
			/*
			// move down right
			for (int j = 9 + board.player; j < 63; j+=9) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}
			*/

			/*
			// move up left
			for (int j = -9 + board.player; j > 0; j-=9) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move down left
			for (int j = 7 + board.player; j < 63; j+=7) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move up right
			for (int j = -7 + board.player; j > 0; j-=7) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move down
			for (int j = 8 + board.player; j < 63; j+=8) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move up
			for (int j = -8 + board.player; j > 0; j-=8) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move left
			for (int j = board.player -1; j%8 > 0; --j) {
			if(board.board.test(j)) {
			break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
			}

			// move right
			for (int j = board.player +1; j%8 > 0; ++j) {
			if(board.board.test(j)) {
			break;
	}
	board.player = j;
	board.board.set(j);
	algoMin(flag, i, alpha, beta, board);
	board.board.reset(j);
	}
	*/

		} catch(std::runtime_error & e) {
			std::cout << i << "Failure\n";
			break;
		}
	}
	// alert the caller that we have finished
	std::cout << "Exiting\n";
	critical.unlock();
	cv.notify_one();
}

void algoMin(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board board) {
	if (depth == 0) {
		printBoard(board);
		return;
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		int i = depth-1;
		// move down right
		for (int j = 9 + board.opponent; j < 63; j+=9) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up left
		for (int j = -9 + board.opponent; j > 0; j-=9) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move down left
		for (int j = 7 + board.opponent; j < 63; j+=7) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up right
		for (int j = -7 + board.opponent; j > 0; j-=7) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move down
		for (int j = 8 + board.opponent; j < 63; j+=8) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up
		for (int j = -8 + board.opponent; j > 0; j-=8) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move left
		for (int j = board.opponent -1; j%8 > 0; --j) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move right
		for (int j = board.opponent +1; j%8 > 0; ++j) {
			if(board.board.test(j)) {
				break;
			}
			board.opponent = j;
			board.board.set(j);
			algoMax(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

	}
	catch(std::runtime_error & e) {
		throw e;
	}
}

void algoMax(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board board) {
	if (depth == 0) {
		printBoard(board);
		return;
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		int i = depth-1;
		// move down right
		for (int j = 9 + board.player; j < 63; j+=9) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up left
		for (int j = -9 + board.player; j > 0; j-=9) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move down left
		for (int j = 7 + board.player; j < 63; j+=7) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up right
		for (int j = -7 + board.player; j > 0; j-=7) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move down
		for (int j = 8 + board.player; j < 63; j+=8) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move up
		for (int j = -8 + board.player; j > 0; j-=8) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move left
		for (int j = board.player -1; j%8 > 0; --j) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

		// move right
		for (int j = board.player +1; j%8 > 0; ++j) {
			if(board.board.test(j)) {
				break;
			}
			board.player = j;
			board.board.set(j);
			algoMin(flag, i, alpha, beta, board);
			board.board.reset(j);
		}

	} catch(std::runtime_error & e) {
		throw e;
	}
}
