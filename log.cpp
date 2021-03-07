#include "log.h"


std::vector<int> Log::getCLog() const {
	return computerLog;
}

std::vector<int> Log::getOLog() const {
	return opponentLog;
}

void Log::recordComputer(int i) {
	computerLog.push_back(i);
}

void Log::recordOpponent(int i) {
	opponentLog.push_back(i);
}
