#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

#include <array>

struct Record {
  unsigned long long hash{};
  int move{};
};

class Transposition {
private:
  std::array<Record, 196613> *arr;

public:
  Transposition();
  ~Transposition();
  int lookUp(unsigned long long) const;
  void update(unsigned long long, int);
};

#endif
