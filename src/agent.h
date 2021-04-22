#ifndef AGENT_H
#define AGENT_H

#include "board.h"
#include "transposition.h"
#include <atomic>
#include <condition_variable>
#include <mutex>
#include <unordered_map>

class Agent {

private:
#ifdef DEBUG
  long long counter;
  long long prunedHits;
  long long regularHits;
  long long collisions;
#endif
  int wrapper(const Board);
  int algoMin(std::atomic<bool> &, const int, int, int, Board &);
  int algoMax(std::atomic<bool> &, const int, int, int, Board &);
  void minMax(std::condition_variable &, std::atomic<bool> &, Board, int &);

  // the evelauation function
  int evaluate(const Board);
  int count(const Board board, const int playerPosition);

  Transposition table;

public:
  Agent();

  int getAiTurn(const Board);
};

#endif
