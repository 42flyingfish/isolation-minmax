# isolation-minmax
Let's use adversarial search to play the board game isolation
This was originally created as a final assignment for a University Artificial Intelligence class
This agent uses a minmax algorithm with alpha beta pruning to search for the next move.
The assignment imposed the time limit of having the agent return a move in no more than 20 seconds.
After this time limit is reached or the agent exhausted the search space, the agent returns the best evaluated move so far.
This time limit can lead to imperfect solutions being returned.

## Rules of the game
* The board is an 8 by 8 board
* The players start in opposing corners of the board
* Each player moves in the same manner as a chess queen
* Places where players once were are now marked as being blocked
* A player can not occupy or pass through a blocked square on the board.
* A player that can no longer move has lost the game.

## Heuristics
The current heuristic is rather simple. It is the difference of the number of moves the two players can make. The simple heuristic allows for quick evaluations.
### Weakness to resolve
* Late game, the board my be in a state where the two players are isolated from one another. In such a case, another tactic would be to maximize the amount of turns possible to outlast the opponent.
