#include "interface.h"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// prints board state
void printBoard(const Board board, const Log log) {

  std::vector<int> computerLog = log.getCLog();
  std::vector<int> opponentLog = log.getOLog();

  auto cit = computerLog.begin();
  auto oit = opponentLog.begin();

  std::cout << "  1 2 3 4 5 6 7 8     Computer vs. Opponent" << std::endl;
  for (unsigned int i = 0; i < 8; ++i) {
    std::cout << char('A' + i);
    for (int j = 0; j < 8; ++j) {
      int index = i * 8 + j;
      if (board.test(index)) {
        if (index == board.getComputer()) {
          std::cout << ' ' << 'X';
        } else if (index == board.getOpponent()) {
          std::cout << ' ' << 'O';
        } else {
          std::cout << ' ' << '#';
        }
      } else {
        std::cout << ' ' << '-';
      }
    }

    // printing the log
    //
    // check if log is not empty
    if (cit != computerLog.end() || cit != opponentLog.end()) {

      // print number
      std::cout << "        " << i + 1 << ". ";

      if (cit != computerLog.end()) {
        printMove(*cit);
        cit++;
      } else {
        std::cout << "  ";
      }

      // spacer
      std::cout << "   ";

      if (oit != opponentLog.end()) {
        printMove(*oit);
        oit++;
      }
    }
    std::cout << std::endl;
  }
  // check if log is not empty
  for (int i = 8; cit != computerLog.end() || oit != opponentLog.end(); ++i) {

    // print number
    if (i == 8 || i == 9) {
      std::cout << "                         " << i << ". ";
    } else {
      std::cout << "                        " << i << ". ";
    }

    if (cit != computerLog.end()) {
      printMove(*cit);
      cit++;
    } else {
      std::cout << "  ";
    }

    // spacer
    std::cout << "   ";

    if (oit != opponentLog.end()) {
      printMove(*oit);
      oit++;
    }

    std::cout << std::endl;
  }
  std::cout << "\n\n";
}

void printMove(const int move) {
  char letter = 'A' + move / 8;

  // Plus one is needed due to moves starting at 0
  int num = move % 8 + 1;

  std::cout << letter << num;
}

int getUserInput(const Board board) {
  std::string value;

  auto successor = board.expandOpp();

  while (1) {
    std::cout << "Enter opponent’s move: ";
    if (!std::getline(std::cin, value)) {
      std::cout << "Somehow an io error occured. Let's try that again\n";
    }
    if (value.length() != 2) {
      std::cout << "Please enter a string of length 2\n";
    } else if (value[0] < 'A' || value[0] > 'H') {
      std::cout
          << "Must start with a capital letter between A and H inclusive\n";
    } else if (value[1] < '1' || value[1] > '8') {
      std::cout << "Must end with a digit between 1 and 8 inclusive\n";
    } else {
      int move = (value[0] - 'A') * 8 + value[1] - '1';
      if (board.test(move)) {
        std::cout << "Already blocked\n";
      } else {
        for (const auto state : successor) {
          if (state == move) {
            return move;
          }
        }
        std::cout << "Not a valid move\n";
      }
    }
  }
}

bool computerStartGame() {
  std::string value;
  while (1) {
    std::cout << "Who should start? Computer or Opponent (C/O): ";
    if (!std::getline(std::cin, value)) {
      std::cout << "Somehow an io error occured. Let's try that again\n";
    }
    if (value == "C") {
      return true;
    } else if (value == "O") {
      return false;
    } else {
      std::cout << "Input must be C or O\n";
    }
  }

  return false;
}
