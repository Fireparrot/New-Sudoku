# New-Sudoku

This is a remake of one of the oldest C++ programs I made: a sudoku solver.

---

The intention was to apply newer concepts that I learned and see how much I improved.

The old code is scattered/in disrepair, so I cannot show it off here, but I do have the newer, remade version.
The old version was messy and incapable of guessing, while this newer version is more structured and recursively guesses when it is stuck.

Most of this code was written in 2015. For presentation purposes, I fixed up some code (November 2020).

---

## Running

To compile the code, type (into the command line)
```
g++ Sudoku.cpp Board.hpp -o sudoku
```

Alternatively, type
```
g++ Sudoku.cpp Board.hpp -D DEBUG -o sudoku
```
to compile with some output features on.

Afterwards, running
```
./sudoku
```
will solve the test board given inside Sudoku.cpp

---

## Note about Data

The test board that is solved is pulled from Wikipedia (https://en.wikipedia.org/wiki/Sudoku) and hard-coded into Sudoku.cpp

It is possible to edit the hard-coded values, recompile and run. 
