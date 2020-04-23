#ifndef AGENT_H
#define AGENT_H

#include <atomic>
#include <condition_variable>
#include "board.h"
#include <mutex>

void getAiTurn(const Board);
void wrapper(const Board);
void algoMin(std::atomic<bool> &, const int, int, int, Board);
void algoMax(std::atomic<bool> &, const int, int, int, Board);
void minMax(std::condition_variable &, std::atomic<bool> &, Board, std::mutex &);

#endif
