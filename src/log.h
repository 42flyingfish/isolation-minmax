#ifndef LOG_H
#define LOG_H

#include <vector>

class Log {
private:
  std::vector<int> computerLog;
  std::vector<int> opponentLog;

public:
  std::vector<int> getCLog() const;
  std::vector<int> getOLog() const;

  void recordComputer(int i);
  void recordOpponent(int i);
};
#endif
