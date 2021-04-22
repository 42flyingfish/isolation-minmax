#include "transposition.h"
#include <iostream>

Transposition::Transposition() {
  arr = new std::array<Record, 196613>;
  for (auto &&r : *arr) {
    r.hash = 0;
    r.move = -1;
  }
}

Transposition::~Transposition() { delete arr; }

int Transposition::lookUp(unsigned long long hash) const {
  auto index = hash % arr->max_size();
  Record val = arr->at(index);
  if (val.hash != hash) {
    return -1;
  } else {
    return val.move;
  }
}

void Transposition::update(unsigned long long hash, int move) {
  Record &val = arr->at(hash % arr->max_size());
  val.hash = hash;
  val.move = move;
}
