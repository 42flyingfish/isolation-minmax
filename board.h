#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <vector>

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

		void undoComputer(const int old);
		void undoOpponent(const int old);

		bool test(const size_t) const;
		bool gameOver() const;

		int getComputer() const;
		int getOpponent() const;

		std::vector<int> expandComp() const;
		std::vector<int> expandOpp() const;

		bool operator==(const Board &other) const;


		// used only with agent vs agent testing
		void swapPlayer();
		void reset();

		std::bitset<64> getBitset() const;
};

#endif
