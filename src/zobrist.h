#ifndef ZOBRIST_H
#define ZOBRIST_H

#include <array>

class Zobrist {
private:
  std::array<unsigned long long, 64> blocked;
  std::array<unsigned long long, 64> computer;
  std::array<unsigned long long, 64> opponent;

public:
  Zobrist();
  unsigned long long getBlockHash(int i) const;
  unsigned long long getOpponentHash(int i) const;
  unsigned long long getComputerHash(int i) const;
};

#endif
