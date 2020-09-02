#ifndef BOARD_H
#define BOARD_H

#include <bitset>
#include <vector>

class Board {
	private:
		std::bitset<64> board;
		int computer;
		int opponent;
		std::vector<int> computerLog;
		std::vector<int> opponentLog;

		bool canMoveFrom(const int) const;

	public:
		Board();
		Board(const int x, const int y);
		
		void moveComputer(const int);
		void moveOpponent(const int);

		// this may or may not be a speed boost
		// as it does interact with the vector
		void moveComputerNoLogging(const int);
		void moveOpponentNoLogging(const int);

		bool test(const size_t) const;
		bool gameOver() const;

		int getComputer() const;
		int getOpponent() const;

		std::vector<int> expandComp() const;
		std::vector<int> expandOpp() const;

		std::vector<int> getCLog() const;
		std::vector<int> getOLog() const;


		bool operator==(const Board &other) const;


		// used only with agent vs agent testing
		void swapPlayer();
		void reset();

		std::bitset<64> getBitset() const;
};

#endif
