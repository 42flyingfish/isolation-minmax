#include "zobrist.h"
#include <limits>
#include <random>

Zobrist::Zobrist() {

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<unsigned long long> dis(
      std::numeric_limits<unsigned long long>::min(),
      std::numeric_limits<unsigned long long>::max());

  for (auto &&it : blocked) {
    it = dis(gen);
  }

  for (auto &&it : opponent) {
    it = dis(gen);
  }

  for (auto &&it : computer) {
    it = dis(gen);
  }
}

unsigned long long Zobrist::getBlockHash(int i) const { return blocked.at(i); }

unsigned long long Zobrist::getComputerHash(int i) const {
  return computer.at(i);
}

unsigned long long Zobrist::getOpponentHash(int i) const {
  return opponent.at(i);
}
