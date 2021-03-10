#include <iostream>
#include "agent.h"
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
	std::mutex m;
	std::condition_variable cv;
	std::atomic<bool> flag {false};
	int move;

	std::thread worker(&Agent::minMax, this, std::ref(cv), std::ref(flag), board, std::ref(move));

	std::unique_lock<std::mutex> l{m};
	if (cv.wait_for(l, std::chrono::seconds(20)) == std::cv_status::timeout) {

		// set timeout flag to be read by thread
		flag = true;
	}
	// waiting for minMax to finish
	worker.join();
	return move;
} 


void Agent::minMax(std::condition_variable & cv, std::atomic<bool> & flag, Board board, int & move) {

	// init alpha beta
	constexpr int alpha{std::numeric_limits<int>::min()};
	constexpr int beta{std::numeric_limits<int>::max()};

	auto priorMove{board.getComputer()};
	auto successors = board.expandComp();
#if DEBUG
	int val{};
	counter = 0;
#endif
	try {
		int score{alpha};
		for (const auto & it : successors) {
			board.moveComputer(it);
			auto lscore = algoMin(flag, 0, alpha, beta, board);
			board.undoComputer(priorMove);
			if (lscore > score) {
				lscore = score;
				move = it;
			}
		}

		for (int depth = 0; depth <= 64; ++depth) {
#if DEBUG
			val = depth;
#endif
			board.moveComputer(move);
			int score = algoMin(flag, depth, alpha, beta, board);
			board.undoComputer(priorMove);

			for (const auto & it : successors) {
				board.moveComputer(it);
				auto lscore = algoMin(flag, depth, alpha, beta, board);
				board.undoComputer(move);
				if (lscore > score) {
					lscore = score;
					move = it;
				}
			}
		}

	} catch(std::runtime_error & e) {
#if DEBUG
		std::cout << "Depth is " << val << std::endl;
		std::cout << "Counter is " << counter << std::endl;
#endif
		return;
	}
	// alert the caller that we have finished
	cv.notify_one();
} 

int Agent::algoMin(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board & board) {
#if DEBUG
	++counter;
#endif
	if (depth == 0 ) {
		return -evaluate(board, board.getOpponent(), board.getComputer());
	}

	if (flag) {
		throw std::runtime_error("Timeout");
	}

	auto priorMove{board.getOpponent()};
	auto successors = board.expandOpp();

	if (successors.empty()) {
		return -evaluate(board, board.getOpponent(), board.getComputer());
	}

	for (const auto & state : successors) {
		board.moveOpponent(state);
		int value = algoMax(flag, depth-1, alpha, beta, board);
		board.undoOpponent(priorMove);
		if (value <= alpha) {
			return alpha;
		}
		if (value < beta) {
			beta = value;
		}
	}

	return beta;
}

int Agent::algoMax(std::atomic<bool> & flag, const int depth, int alpha, int beta, Board & board) {
#if DEBUG
	++counter;
#endif
	if (depth == 0 ) {
		return evaluate(board, board.getComputer(), board.getOpponent());
	}

	if (flag) {
		throw std::runtime_error("Timeout");
	}

	auto priorMove{board.getComputer()};
	auto successors = board.expandComp();

	if (successors.empty()) {
		return evaluate(board, board.getComputer(), board.getOpponent());
	}

	for (const auto & state : successors) {
		board.moveComputer(state);
		int value = algoMin(flag, depth-1, alpha, beta, board);
		board.undoComputer(priorMove);
		if (value >= beta) {
			return value;
		}
		if (value > alpha) {
			alpha = value;
		}
	}

	return alpha;
}


// The evaluation function
int Agent::evaluate(const Board board, const int player, const int opponent) {
	int aMax = count(board, player);
	int aMin = count(board, opponent);
	int score;
	if (board.getBitset().count() < 32) {
		score = 2 * aMax - aMin;
	} else {
		score = aMax - aMin * 2;
	}
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
