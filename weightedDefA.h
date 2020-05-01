#ifndef WEIGHTEDDEFA_H
#define WEIGHTEDDEFA_H

#include <atomic>
#include <condition_variable>
#include "board.h"
#include <mutex>

class WeightedDeffA {

	private:

		int wrapper(const Board);
		int algoMin(std::atomic<bool> &, const int, int, int, Board);
		int algoMax(std::atomic<bool> &, const int, int, int, Board);
		void minMax(std::condition_variable &, std::atomic<bool> &, const Board, std::mutex &, int &);

		// the evelauation function
		int evaluate(const Board, const int pos, const int opp) const;
		int count(const Board board, const int playerPosition) const;

	public:
		WeightedDeffA() = default;

		int getAiTurn(const Board);

};

#endif
