#ifndef BOARD_H
#define BOARD_H

#include <bitset>

class Board {
	private:
		std::bitset<64> board;
		int computer;
		int opponent;

	public:
		Board();
		
		void moveComputer(const int);
		void moveOpponent(const int);
		bool test(const size_t) const;

		int getComputer() const;
		int getOpponent() const;


		// used only with agent vs agent testing
		void swapPlayer();
};

#endif
