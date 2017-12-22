

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sudokusolver.h"

#define TRUE 1
#define FALSE 0
#define n 9

void printBoard(int board[][9]){
  int i,j;
  printf("--------------\n");
  for ( i=0; i<9;i++){
    for (j=0; j<9;j++){
      printf("%d",board[i][j]);
      if ((j+1)%3==0) printf(" | ");
    }
    printf("\n");
    if ((i+1)%3==0) printf("--------------\n");
  }
  printf("\n");
}

void print81board(int* board){
  int i,j;
  printf("--------------\n");
  for ( i=0; i<9;i++){
    for (j=0; j<9;j++){
      printf("%d",board[i*9+j]);
      if ((j+1)%3==0) printf(" | ");
    }
    printf("\n");
    if ((i+1)%3==0) printf("--------------\n");
  }
  printf("\n");

}

int isAvailable(int board[][9], int row, int col, int num){
  //int n=9;
  int i;
  for(i=0;i<n;i++){
    if (board[row][(col+i)%9] ==num || //column
      board [(row+i)%9][col] ==num ||//row
      board[((row/3) * 3) + (i%3)][((col/3) * 3) + (i/3)]==num)//quadrant
      return FALSE;
  }
  return TRUE;
}

int isFull(int board[][9]){
  //int n=9;//all the boards we're solving are 9x9,
  //instead get this from an input arg if different size
  int i,j;
  for(i=0;i<n;i++){
    for (j = 0; j<n; j++) {
      if(!board[i][j])//checks for zeroes (blank)
        return FALSE;
    }
  }
  return TRUE;
}


int isSolvedBoard(int board[][9]){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      //for every value, check that it's not repeated in any other places
      if(isAvailable(board, i, j, board[i][j]))
        return FALSE;
    }
  }
  //if everything's available
  return isFull(board);
}

//takes a 9x9 board and prints it to a 81 int array
//returns the pointer to that 81 array
int* to81array(int board[9][9]){
  int i,j;
  int* newBoard = malloc(sizeof(int) * (81));
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      newBoard[(i*n+j)]= board[i][j];
    }
  }
  return newBoard;
}



//from 81 int array to 9x9 array
//takes the pointer to a 81 int array
int** to9x9array(int board[81]){
  int** array = createArray();
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      array[i][j]= board[(i*n+j)];
    }
  }
  return array;
}



int** createArray(){
    int* values = calloc(n*n, sizeof(int));
    int** rows = malloc(n* sizeof(int*));
    for (int i=0; i<n; ++i)
    {
        rows[i] = values + i*n;
    }
  return rows;
}

//copies from second input to first input
void copyboard(int solution [9][9], int** board){
  int i,j;
  for(i = 0; i<9; i++){
    for(j=0;j<9;j++){
      solution[i][j]=board[i][j];
    }
  }
}


int isValid(int board[][9]){
  int i,j;
  for(i=0;i<9;i++){
    for(j=0;j<9;j++){
      if(!isAvailable(board,i,j,board[i][j]))
        return FALSE;
    }
  }
  return TRUE;
}
