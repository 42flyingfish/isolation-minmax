#ifndef BUCKETAGENT_H
#define BUCKETAGENT_H

#include <atomic>
#include <condition_variable>
#include "board.h"
#include <bitset>
#include <unordered_map>
#include <mutex>

class BucketAgent {

	private:

		std::unordered_map<std::bitset<64>, bool> terminalMap;

		int wrapper(const Board);
		int algoMin(std::atomic<bool> &, const int, int, int, Board);
		int algoMax(std::atomic<bool> &, const int, int, int, Board);
		void minMax(std::condition_variable &, std::atomic<bool> &, const Board, std::mutex &, int &);
		bool isTerminal(const Board);

		// the evelauation function
		int evaluate(const Board);
		int count(const Board board, const int playerPosition);

	public:

		int getAiTurn(const Board);

};

#endif
