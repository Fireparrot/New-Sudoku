#include <iostream>
#include "Board.hpp"

//#define DEBUG 

#ifdef DEBUG
	#define LOG(x) std::cout << x;
#else
	#define LOG(x) ;
#endif

template<unsigned int N>
USI solve(Sudoku<N>& board, int recursion = 0) {
	 do {
		board.scan();
		if(board.status(board.STUCK)) {
			USI i, j, n;
			board.recordLeastUncertainSpot(i, j, n);

			Sudoku<N> test = Sudoku<N>(board);
			test(i, j) = n+1;
			LOG(std::string(recursion, '-') << "Testing (" << i << ", " << j << ") = " << n+1 << std::endl)
			USI result = solve(test, recursion + 1);
			if(result&board.FINISHED) {
				board = test;
				return board.FINISHED;
			} else {
				board(i, j, n) = false;
				LOG(std::string(recursion, '-') << "FAILURE (" << i << ", " << j << ") = " << n+1 << std::endl)
			}
		}
	} while(board.status(board.UNFINISHED|board.STUCK));

	if(board.status(board.IMPOSSIBLE)) {
		LOG(std::string(recursion, '-') << "Failed to solve" << std::endl)
	}

	return board.status();
}

int main() {

	/*USI nums [16][16]= {
			{2 , 15, 0 , 0 ,    0 , 0 , 0 , 0 ,    0 , 0 , 10, 7 ,    0 , 0 , 0 , 0 },
			{7 , 0 , 0 , 13,    0 , 0 , 0 , 0 ,    0 , 11, 16, 0 ,    0 , 0 , 0 , 3 },
			{1 , 0 , 0 , 4 ,    2 , 0 , 0 , 16,    8 , 0 , 0 , 5 ,    0 , 0 , 10, 15},
			{0 , 11, 6 , 16,    0 , 0 , 5 , 14,    2 , 0 , 13, 3 ,    0 , 0 , 12, 9 },

			{0 , 8 , 2 , 7 ,    6 , 0 , 13, 9 ,    16, 3 , 1 , 15,    10, 0 , 0 , 12},
			{14, 1 , 11, 6 ,    16, 12, 0 , 4 ,    7 , 13, 0 , 10,    9 , 0 , 3 , 0 },
			{16, 0 , 0 , 0 ,    0 , 0 , 3 , 0 ,    0 , 0 , 0 , 9 ,    2 , 0 , 0 , 8 },
			{5 , 0 , 15, 0 ,    10, 0 , 0 , 2 ,    0 , 8 , 0 , 0 ,    0 , 4 , 13, 0 },

			{0 , 16, 4 , 0 ,    0 , 0 , 6 , 0 ,    9 , 0 , 0 , 1 ,    0 , 11, 0 , 7 },
			{12, 0 , 0 , 11,    15, 0 , 0 , 0 ,    0 , 4 , 0 , 0 ,    0 , 0 , 0 , 6 },
			{0 , 13, 0 , 3 ,    4 , 0 , 15, 11,    10, 0 , 6 , 15,    16, 12, 5 , 2 },
			{6 , 0 , 0 , 10,    1 , 2 , 12, 8 ,    13, 16, 0 , 11,    15, 3 , 9 , 0 },

			{9 , 5 , 0 , 0 ,    12, 0 , 0 , 1 ,    11, 15, 0 , 0 ,    3 , 6 , 7 , 0 },
			{3 , 6 , 0 , 0 ,    8 , 0 , 0 , 13,    4 , 0 , 0 , 12,    5 , 0 , 0 , 10},
			{13, 0 , 0 , 0 ,    0 , 3 , 9 , 0 ,    0 , 0 , 0 , 0 ,    12, 0 , 0 , 11},
			{0 , 0 , 0 , 0 ,    5 , 14, 0 , 0 ,    0 , 0 , 0 , 0 ,    0 , 0 , 2 , 13}

	};*/

	// Puzzle from Wikipedia:
	// https://en.wikipedia.org/wiki/Sudoku
	USI nums[9][9] = {
		{0, 0, 0,	2, 1, 0,	0, 0, 0},
		{0, 0, 7,	3, 0, 0,	0, 0, 0},
		{0, 5, 8,	0, 0, 0,	0, 0, 0},

		{4, 3, 0,	0, 0, 0,	0, 0, 0},
		{2, 0, 0,	0, 0, 0,	0, 0, 8},
		{0, 0, 0,	0, 0, 0,	0, 7, 6},

		{0, 0, 0,	0, 0, 0,	2, 5, 0},
		{0, 0, 0,	0, 0, 7,	3, 0, 0},
		{0, 0, 0,	0, 9, 8,	0, 0, 0}
	};


	Sudoku<3> board = Sudoku<3>(nums);
	board.print();
	solve(board);
	std::cout << std::endl;
	board.print();
	//board.print2();
}
