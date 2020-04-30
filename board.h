#ifndef BOARD_H
#define BOARD_H

#include <bitset>

class Board {
	private:
		std::bitset<64> board;
		int computer;
		int opponent;

		bool canMoveFrom(const int) const;

	public:
		Board();
		Board(const int x, const int y);
		
		void moveComputer(const int);
		void moveOpponent(const int);
		bool test(const size_t) const;
		bool gameOver() const;

		int getComputer() const;
		int getOpponent() const;


		// used only with agent vs agent testing
		void swapPlayer();
};

#endif
