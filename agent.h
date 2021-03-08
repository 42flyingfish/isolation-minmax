#ifndef AGENT_H
#define AGENT_H

#include <atomic>
#include <condition_variable>
#include "board.h"
#include <mutex>
#include <unordered_map>

class Agent {

	private:

		long long counter;
		int wrapper(const Board);
		int algoMin(std::atomic<bool> &, const int, int, int, Board &);
		int algoMax(std::atomic<bool> &, const int, int, int, Board &);
		void minMax(std::condition_variable &, std::atomic<bool> &, Board, int &);
		std::unordered_map<std::bitset<64>, int> table;


		// the evelauation function
		int evaluate(const Board, const int, const int);
		int count(const Board board, const int playerPosition);

	public:
		Agent() = default;

		int getAiTurn(const Board);

};

#endif
