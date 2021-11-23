# isolation-minmax
Let's use adversarial search to play the board game isolation.
This was originally created as a final assignment for a University Artificial Intelligence class.
This agent uses a minmax algorithm with alpha beta pruning to search for the next move.
The assignment imposed the time limit of having the agent return a move in no more than 20 seconds.
After this time limit is reached or the agent exhausted the search space, the agent returns the best evaluated move so far.
This time limit can lead to imperfect solutions being returned.

## Rules of the game
* The board is an 8 by 8 board
* The players start in opposing corners of the board
* Each player moves in the same manner as a chess queen with a few restrictions
  * Places where players once were are now marked as being blocked
  * A player can not occupy or pass through a blocked square on the board.
  * Multiple players can not occupy the same square
* A player that can no longer move has lost the game.
  * As such, there are no draws in this game

## Heuristic
The current heuristic is rather simple. It is the difference of the number of moves the two players can make. The simple heuristic allows for quick evaluations.

## Compiling and Running
* The project was written in C++17 on Ubuntu Linux using the GCC compiler.
* Included is a Makefile that will build the project.
* If the macro DEBUG is set, the agent will print information such as the greatest depth reached before the timeout.
* Once started, the game will ask for who will go first.
  * Users are expected to answer with C or a O for computer or opponent (human) respectively.
  * Following that, the Computer and the player will take turns making moves until the game ends.
  * The player can submit moves by typing in the respective Letter and Number representing the column and row of the board to move to.
  * The computer is limited to taking 20 seconds at most to consider a turn.

## Future Improvements and Considerations

### Zobrist Hashing
* The project has experimental support for zobrist hasing
* By early, I mean code that has largely been untested in terms of performance.
* In the current implementation there are four sets of hashes. The first two are for occupied and unoccupied squares on the board. The final two are for the two players in the game. All four sets are randomly generated and exist as an inline static member.

#### Concerns and TODOs regarding the Hashing code
* Perform test to see how large the table and hashes or keys should be.
* See if this makes any noticible change in regards performance.
  * In the best case scenario, move generation is skipped entirely for min or max.
* Check if the key collisions result in illegal moves being considered.
  * For now, the root of alpha beta doesn't use the table to avoid returning an invalid move.
  * Keys are stored along within the table to make a quick check for index collisions.
* Currently, the agent will always replace an entry on the table. Is this a good idea? Should depth be considered? Should the score be considered?

### Better or Alternative Heuristics
* Late game, the board my be in a state where the two players are isolated from one another. In such a case, another tactic would be to maximize the amount of turns possible to outlast the opponent.

### Killer Heuristic
* A possible future addition could be a killer heuristic.
* The idea behind this if some move is really good in one board state, it might be a great move in a similar board state.
* It might be a good idea to record the moves that produced a cutoff at a certain depth and try those again.

### Better GUI
* The console interface is a bit clunky and could use an update.

### Configuration Options
* There is currently no way to configure the game outside of who gets to go first.
  * It might be nice to configure the timeout, runtime information, evaluation function, or allow the AI to compete with itself.
  * Early on in the project, there was an AI vs. AI feature that was used for testing. This was removed upon project submission.
