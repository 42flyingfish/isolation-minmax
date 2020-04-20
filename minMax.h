#ifndef MINMAX_H
#define MINMAX_H

#include <atomic>
#include <condition_variable>
#include "board.h"

void getAiTurn(const Board);
void wrapper();
void algoMin(std::atomic<bool> &, const int, const int, const int);
void algoMax(std::atomic<bool> &, const int, const int, const int);
void minMax(std::condition_variable &, std::atomic<bool> &);

#endif
