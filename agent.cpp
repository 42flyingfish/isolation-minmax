#include "agent.h"
#include "board.h"

#include <atomic> // for std::atomic<bool> 
#include <chrono> // for std::chrono::seconds
#include <condition_variable> // for cv.wait_for
#include <mutex> // used with std::condition_variable
#include <thread> // to run the timeout and minMax function in threads
#include <limits> // to init alpha/beta small/big number


// returns a value to move
int Agent::getAiTurn(const Board board) {
	return wrapper(board);
}

// A wrapper built around the minmax algorithm
// Will set an atomic boolean flag to true after the alloted time has expired
// Also accepts an early notification through the condition_variable
//    so that it does not always take the full alloted time
int Agent::wrapper(const Board board) {
	std::mutex m, critical;
	std::condition_variable cv;
	std::atomic<bool> flag {false};
	int move;

	std::thread third(&Agent::minMax, this, std::ref(cv), std::ref(flag), board, std::ref(critical), std::ref(move));
	third.detach();

	std::unique_lock<std::mutex> l{m};
	if (cv.wait_for(l, std::chrono::seconds(20)) == std::cv_status::timeout) {

		// set timeout flag to be read by thread
		flag = true;
		// waiting for minMax to finish
		critical.lock();
		critical.unlock();
	}
	return move;
}


void Agent::minMax(std::condition_variable & cv, std::atomic<bool> & flag, const Board board, std::mutex & critical, int & move) {

	critical.lock();

	// init alpha beta
	int alpha{std::numeric_limits<int>::min()};
	int beta{std::numeric_limits<int>::max()};

	for (int i=0; i <= 100000; ++i) {
		if (flag) {
			break;
		}
		try {
			// move down right
			for (int j = 9 + board.getComputer(); j%8 > board.getComputer()%8 && j < 64; j+=9) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}
			}

			// move up left
			for (int j = -9 + board.getComputer(); j%8 < board.getComputer() %8 && j > 0; j-=9) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.getComputer();
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}

			}

			// move down left
			for (int j = 7 + board.getComputer(); j%8 < board.getComputer() %8  && j < 64; j+=7) {
				if(board.test(j)) {
					break;
				}
				Board next  = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}

			}

			// move up right
			for (int j = -7 + board.getComputer(); j%8 > board.getComputer()%8 && j > 0; j-=7) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}

			}

			// move down
			for (int j = 8 + board.getComputer(); j < 64; j+=8) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}
			}

			// move up
			for (int j = -8 + board.getComputer(); j > 0; j-=8) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}
			}


			// move left
			for (int j = board.getComputer() -1; j%8 < 7 && j > 0; --j) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}
			}


			// move right
			for (int j = board.getComputer() +1; j%8 > 0; ++j) {
				if(board.test(j)) {
					break;
				}
				Board next = board;
				next.moveComputerNoLogging(j);
				int value = algoMin(flag, i, alpha, beta, next);
				if (value > alpha) {
					alpha = value;
					move = j;
				}
			}

		} catch(std::runtime_error & e) {
			break;
		}
	}
	// alert the caller that we have finished

	// set move and unlock
	cv.notify_one();
	critical.unlock();
}

int Agent::algoMin(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board board) {
	if (depth == 0 ) {
		return evaluate(board);
	}
	if (board.gameOver()) {
		return -1;
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		int i = depth-1;

		// move down right
		for (int j = 9 + board.getOpponent(); j%8 > board.getOpponent()%8 && j < 64; j+=9) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			board.moveOpponent(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}

		// move up left
		for (int j = -9 + board.getOpponent(); j%8 < board.getOpponent()%8 && j > 0; j-=9) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}

		// move down left
		for (int j = 7 + board.getOpponent(); j%8 < board.getOpponent()%8  && j < 64; j+=7) {
			if(board.test(j)) {
				break;
			}
			Board next  = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}

		// move up right
		for (int j = -7 + board.getOpponent(); j%8 > board.getOpponent()%8 && j > 0; j-=7) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}

		// move down
		for (int j = 8 + board.getOpponent(); j < 64; j+=8) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}

		// move up
		for (int j = -8 + board.getOpponent(); j > 0; j-=8) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}


		// move left
		for (int j = board.getOpponent() -1; j%8 < 7 && j > 0; --j) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveOpponentNoLogging(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}


		// move right
		for (int j = board.getOpponent() +1; j%8 > 0; ++j) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			board.moveOpponent(j);
			int value = algoMax(flag, i, alpha, beta, next);
			if (value < beta) {
				beta = value;
				if (alpha >= beta) {
					return beta;
				}
			}
		}


	} catch(std::runtime_error & e) {
		throw e;
	}

	return beta;
}

int Agent::algoMax(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board board) {
	if (depth == 0 ) {
		return evaluate(board);
	}
	if (board.gameOver()) {
		return 1;
		//return evaluate(board);
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		int i = depth-1;

		// move down right
		for (int j = 9 + board.getComputer(); j%8 > board.getComputer()%8 && j < 64; j+=9) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			board.moveComputer(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}

		// move up left
		for (int j = -9 + board.getComputer(); j%8 < board.getComputer()%8 && j > 0; j-=9) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}

		// move down left
		for (int j = 7 + board.getComputer(); j%8 < board.getComputer()%8  && j < 64; j+=7) {
			if(board.test(j)) {
				break;
			}
			Board next  = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}

		// move up right
		for (int j = -7 + board.getComputer(); j%8 > board.getComputer()%8 && j > 0; j-=7) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}

		// move down
		for (int j = 8 + board.getComputer(); j < 64; j+=8) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}

		// move up
		for (int j = -8 + board.getComputer(); j > 0; j-=8) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}


		// move left
		for (int j = board.getComputer() -1; j%8 < 7 && j > 0; --j) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}


		// move right
		for (int j = board.getComputer() +1; j%8 > 0; ++j) {
			if(board.test(j)) {
				break;
			}
			Board next = board;
			next.moveComputerNoLogging(j);
			int value = algoMin(flag, i, alpha, beta, next);
			if (value > alpha) {
				alpha = value;
				if (alpha >= beta) {
					return alpha;
				}
			}
		}



	} catch(std::runtime_error & e) {
		throw e;
	}

	return alpha;
}


// The evaluation function
int Agent::evaluate(const Board board) {
	int aMax = count(board, board.getComputer());
	int aMin = count(board, board.getOpponent());
	int score = aMax - aMin;
	return score;

}

int Agent::count(const Board board, const int playerPosition) {
	int localSum = 0;
	// move down right
	for (int i = 9 + playerPosition; i%8 > playerPosition%8 && i < 64; i+=9) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}


	// move up left
	for (int i = -9 + playerPosition; i%8 < playerPosition%8 && i >= 0; i-=9) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move down left
	for (int i = 7 + playerPosition; i%8 < playerPosition%8  && i < 64; i+=7) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move up right
	for (int i = -7 + playerPosition; i%8 > playerPosition%8 && i >= 0; i-=7) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move down
	for (int i = 8 + playerPosition; i < 64; i+=8) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move up
	for (int i = -8 + playerPosition; i >= 0; i-=8) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move left
	for (int i = playerPosition -1; i%8 < 7 && i >= 0; --i) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}

	// move right
	for (int i = playerPosition +1; i%8 > 0 && i < 64; ++i) {
		if(board.test(i)) {
			break;
		}
		++localSum;
	}
	return localSum;
}
