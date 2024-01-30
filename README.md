# NIM

An artifically intelligent program that can play the game of nim against the user. This program learns to avoid unsafe moves from its losses, and will continue to improve as more games are played.

Algorithm:

The goal of this algorithm is to create a game that learns from its losses in the game of Nim.

The program will use a structure called state to keep track of the state of the game as the machine acts on the board. The machine will read a list of states previously found to lead to a loss from an external file.

 The machine will gather a list of board states after possible moves it can make given the current state of the board. It will then compare the possible next states to the list of unsafe moves as read from the file. Any state that is not included in the unsafe file will be considered safe. The machine will attempt to make a safe move, but if no possible moves are safe, it will make a random move.

Any state that forces the machine to make an unsafe move will be stored as a new unsafe state along with nine extra states reached after adding 1, 2, and 3 to each pile in the current state. At the end of the game, the program will add its newfound unsafe states to the unsafe file, sort the file, and write the extended list into the unsafe file.

To increase the efficiency of the algorithm, several steps were taken. Methods have been written with the return statement as early as possible, so that the machine does not have to read all the code in each method for most cases. The sort algorithm used on the list of unsafe moves will make only one comparison for most of the moves already in the list. Duplicates are removed from the list of unsafe states before sorting, increasing the efficiency of the sort as well.
