#ifndef BOARD_H
#define BOARD_H

#include <bitset>

struct Board {
	std::bitset<64> board;
	int player;
	int opponent;

	Board();
};

#endif
