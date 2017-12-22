#ifndef sudokusolver_h
#define sudokusolver_h

//prints a 9x9 board to the screen
void printBoard(int board[9][9]);
void print81board(int* board);
//returns if that num is allowed in that row,col on the board
int isAvailable(int board[][9], int row, int col, int num);
//returns 1 if the input board is full, 0 if not
int isFull(int board[][9]);
//checks if the baord is solved, 1 if it is, 0 if not
int isSolvedBoard(int board[][9]);
//returns pointer to an 81 board from a 9x9 board
//assumes the memory is consecutive
int* to81array(int board[9][9]);
//returns a 9x9 board from an 81 board
int** to9x9array(int board[81]);
//helper for the above function
int** createArray();
//copies from the second input to the first
void copyboard(int solution [9][9], int** board);
//checks if the input numbers in the board are valid, ie
//if there exists a valis solution to this puzzle
int isValid(int board[][9]);


#endif
