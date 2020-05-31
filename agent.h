#ifndef AGENT_H
#define AGENT_H

#include <atomic>
#include <condition_variable>
#include "board.h"
#include <mutex>

class Agent {

	private:

		int wrapper(const Board);
		int algoMin(std::atomic<bool> &, const int, int, int, Board);
		int algoMax(std::atomic<bool> &, const int, int, int, Board);
		void minMax(std::condition_variable &, std::atomic<bool> &, const Board, std::mutex &, int &);

		// the evelauation function
		int evaluate(const Board, const int, const int);
		int count(const Board board, const int playerPosition);

	public:
		Agent() = default;

		int getAiTurn(const Board);

};

#endif
