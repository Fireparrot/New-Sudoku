/*
 * Board.hpp
 *
 *  Created on: Oct 27, 2015
 *      Author: Nikita Ignatyuk
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <iostream>

typedef unsigned short int USI;

char symbols[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G'};

template<unsigned int N>
class Sudoku {

//public static variables
public:
	static const USI FINISHED = 	0b00000001;
	static const USI UNFINISHED = 	0b00000010;
	static const USI STUCK = 		0b00000100;
	static const USI IMPOSSIBLE = 	0b00001000;

//private variables
private:
	USI board[N*N][N*N];
	bool possible[N*N][N*N][N*N];

//private functions
private:
	inline void elim() {
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				if(board[i][j] != 0) {
					elimDot(i, j);
					elimColumn(i, board[i][j]-1);
					elimRow(j, board[i][j]-1);
					elimSquare(i, j, board[i][j]-1);
				}
			}
		}
	}
	inline void elimDot(USI x, USI y) {
		for(USI n = 0; n < size; ++n) {
			possible[x][y][n] = false;
		}
	}
	inline void elimColumn(USI x, USI n) {
		for(USI y = 0; y < size*size; ++y) {
			possible[x][y][n] = false;
		}
	}
	inline void elimRow(USI y, USI n) {
		for(USI x = 0; x < size*size; ++x) {
			possible[x][y][n] = false;
		}
	}
	inline void elimSquare(USI x, USI y, USI n) {
		USI x_ = x/size;
		USI y_ = y/size;
		for(USI i = 0; i < size; ++i) {
			for(USI j = 0; j < size; ++j) {
				possible[x_*size + i][y_*size + j][n] = 0;
			}
		}
	}

	inline void assign() {
		for(int i = 0; i < size*size; ++i) {
			for(int j = 0; j < size*size; ++j) {
				if(board[i][j] == 0) {
					USI temp = 0;
					USI howMany = 0;
					for(int n = 0; n < size*size; ++n) {
						if(possible[i][j][n]) {
							temp = n;
							++howMany;
						}
					}
					if(howMany == 1) {
						board[i][j] = temp+1;
						elim();
					}
				}
			}
		}
	}
public:
	enum {size = N};

//public constructors
public:
	Sudoku() {
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				board[i][j] = 0;
			}
		}
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				for(int n = 0; n < size*size; ++n) {
					possible[i][j][n] = true;
				}
			}
		}
	}
	Sudoku(USI temp[size*size][size*size]) {
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				board[i][j] = temp[i][j];
			}
		}
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				for(int n = 0; n < size*size; ++n) {
					possible[i][j][n] = true;
				}
			}
		}
	}
	Sudoku(const Sudoku& s) {
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				board[i][j] = s.getBoard(i, j);
			}
		}
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				for(int n = 0; n < size*size; ++n) {
					possible[i][j][n] = s.getPossible(i, j, n);
				}
			}
		}
	}

//public functions
public:
	USI& operator()(USI x, USI y) {return board[x][y];}
	bool& operator()(USI x, USI y, USI n) {return possible[x][y][n];}
	Sudoku& operator=(const Sudoku& s) {
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				board[i][j] = s.getBoard(i, j);
			}
		}
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				for(int n = 0; n < size*size; ++n) {
					possible[i][j][n] = s.getPossible(i, j, n);
				}
			}
		}
		return *this;
	}

	USI getBoard(USI x, USI y) const {return board[x][y];}
	bool getPossible(USI x, USI y, USI n) const {return possible[x][y][n];}

	USI howManyPossible(USI x, USI y) const {
		USI answer = 0;
		for(int n = 0; n < size*size; ++n) {
			if(possible[x][y][n]) {
				++answer;
			}
		}
		return answer;
	}

	void recordLeastUncertainSpot(USI & x, USI & y, USI & lowestN) {
		USI x_ = 0, y_ = 0, howMany = 9;
		for(USI i = 0; i < size*size; ++i) {
			for(USI j = 0; j < size*size; ++j) {
				USI howMany_ = howManyPossible(i, j);
				if(howMany_ > 0 && howMany_ < howMany) {
					x_ = i;
					y_ = j;
					howMany = howMany_;
				}
			}
		}
		x = x_;
		y = y_;
		for(USI n = 0; n < size*size; ++n) {
			if(possible[x][y][n]) {
				lowestN = n;
				return;
			}
		}
	}

	Sudoku& scan() {
		elim();
		assign();
		return *this;
	}

	USI status() {
		USI status = FINISHED;
		for(int i = 0; i < size*size; ++i) {
			for(int j = 0; j < size*size; ++j) {
				if(board[i][j] == 0) {
					USI howMany = howManyPossible(i, j);
					if(howMany > 1) {
						if(status == FINISHED) {
							status = STUCK;
						}
					} else if(howMany == 1) {
						status = UNFINISHED;
					} else if(howMany == 0) {
						return status = IMPOSSIBLE;
					}
				}
			}
		}
		return status;
	}
	bool status(USI s) {
		return status()&s;
	}

	Sudoku& print() {
		for(int i = 0; i < size*size; ++i) {
			for(int j = 0; j < size*size; ++j) {
				std::cout << symbols[board[i][j]] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		return *this;
	}
	Sudoku& print2() {
			for(int i = 0; i < size*size; ++i) {
				for(int j = 0; j < size*size; ++j) {
					if(board[i][j] != 0) {
						std::cout << symbols[board[i][j]];
					}
					for(int n = 0; n < size*size; ++n) {
						if(possible[i][j][n]) {
							std::cout << symbols[n+1];
						}
					}
					std::cout << " ";
				}
				std::cout << std::endl;
			}
			return *this;
		}

};



#endif /* BOARD_HPP_ */
