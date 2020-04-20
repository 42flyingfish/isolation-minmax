#include "minMax.h"
#include "board.h"

#include <atomic> // for std::atomic<bool> 
#include <chrono> // for std::chrono::seconds
#include <condition_variable> // for cv.wait_for
#include <iostream>
#include <mutex> // for std::condition_variable
#include <thread> // to run the timeout and minMax function in threads
#include <limits> // to init alpha/beta small/big number

// returns a value to move
void getAiTurn(const Board board) {
	std::cout << "Hello\n";
	wrapper();
	std::cout << "Done\n";
}

// A wrapper built around the minmax algorithm
// Will set an atomic boolean flag to true after the alloted time has expired
// Also accepts an early notification through the condition_variable
//    so that it does not always take the full alloted time
void wrapper() {
	std::mutex m;
	std::condition_variable cv;
	std::atomic<bool> flag {false};

	std::thread third(minMax, std::ref(cv), std::ref(flag));
	third.detach();

	std::unique_lock<std::mutex> l{m};
	if (cv.wait_for(l, std::chrono::seconds(20)) == std::cv_status::timeout) {

		// set timeout flag to be read by thread
		flag = true;
		std::cout << "Tick tock!\n";
		// waiting for minMax to finish
		cv.wait(l); 
	} else {
		std::cout << "Algorithm returned Early\n";
	}
	return;
}


void minMax(std::condition_variable & cv, std::atomic<bool> & flag) {

	// init alpha beta
	int alpha{std::numeric_limits<int>::min()};
	int beta{std::numeric_limits<int>::max()};

	for (int i=0; i <= 1000; ++i) {
		if (flag) {
			std::cout << i << "Exiting loop\n";
			break;
		}
		try {
			algoMin(flag, i, alpha, beta);
		} catch(std::runtime_error & e) {
			std::cout << i << "Failure\n";
			break;
		}
	}
	// alert the caller that we have finished
	cv.notify_one();
}

void algoMin(std::atomic<bool> & flag, const int depth, const int alpha, const int beta) {
	if (depth == 0) {
		return;
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		algoMax(flag, depth-1, alpha, beta);
	} catch(std::runtime_error & e) {
		throw e;
	}
}

void algoMax(std::atomic<bool> & flag, const int depth, const int alpha, const int beta) {
	if (depth == 0) {
		return;
	}
	if (flag) {
		throw std::runtime_error("Timeout");
	}
	try {
		algoMin(flag, depth-1, alpha, beta);
	} catch(std::runtime_error & e) {
		throw e;
	}
}
