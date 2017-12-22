/*

Michael Folz maf152
eecs 338 final project
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include "sudokusolver.h"

#define TRUE 1
#define FALSE 0
#define n 9


int sockfds [10];
pthread_t listenerthreads [5];



void error(const char *msg){
    perror(msg);
    exit(1);
}

//opens the socket on the input port
//hardcoded for socket 8000, 8001, 8002, 8003, 8004
int openSocket(int input){

     int sockfd, newsockfd, portno;
     socklen_t clilen;
     int buffer[81];
     struct sockaddr_in serv_addr, cli_addr;
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0){
      error("ERROR opening socket");
       return -1;
     }

     //zero the buffer?
     bzero((char *) &serv_addr, sizeof(serv_addr));

     //gets the port no from input
     portno= input;

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     //binding and error check
     if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
       error("ERROR on binding");
       return -1;
     }

     listen(sockfd,5);

     clilen = sizeof(cli_addr);
     //blocks until comething connects

     newsockfd = accept(sockfd,
                 (struct sockaddr *) &cli_addr,
                 &clilen);

     if (newsockfd < 0)
          error("ERROR on accept");

     //store the values of the sockets in sockfds
     //0-4 is sockfd, 5-9 is newsockfd
     sockfds[(input-8000)]=sockfd;
     sockfds[(input-8000+5)]=newsockfd;

     return 0;
}

//closes all sockets that are saved.
int closeSockets(int input [10]){
  int i;
  for(i=0;i<10;i++){
      if(close(input[i])==-1)
        return -1;
  }
  return 0;
}

//stubs, writen below
int solve(int board[][9], int row, int col);


//pthread that listens for input at each socket
//if no input then the thread just waits
//input is an int pointer, tells it where to watch from sockfds
//listens on port 8000
void *listenerthread8000 (){
  printf("starting listener thread 0\n" );

  openSocket(8000);

  int* buffer = malloc(sizeof(int)*(n*n));
  int sockfd=sockfds[5];

  //sockfd is the value our socket is reading and writing from
  //printf("sockfd is open at %d\n",sockfd);
  int i,tmp;
  for(i=0;i<n*n;i++){
    if(read(sockfd,&tmp, sizeof(int))<0){
      error("error reading from the socket");
      pthread_exit(NULL);
    }
    buffer[i]=tmp;
  }

  int solution [9][9];

  copyboard(solution, to9x9array(buffer));
  solve(solution,0,0);

  buffer = to81array(solution);

  for(i=0;i<n*n;i++){
    tmp=buffer[i];
    if(write(sockfd,&tmp, sizeof(int))<0){
        error("error writing to the socket");
        pthread_exit(NULL);
      }
    }

  pthread_exit(NULL);
}

void *listenerthread8001(){
  printf("starting listener thread 1\n" );

  openSocket(8001);



  int* buffer = malloc(sizeof(int)*(n*n));
  int sockfd=sockfds[6];

  //sockfd is the value our socket is reading and writing from
  int i,tmp;
  for(i=0;i<n*n;i++){
    if(read(sockfd,&tmp, sizeof(int))<0){
      error("error reading from the socket");
      pthread_exit(NULL);
    }
    buffer[i]=tmp;
  }

  int solution [9][9];

  copyboard(solution, to9x9array(buffer));
  solve(solution,0,0);

  buffer = to81array(solution);

  for(i=0;i<n*n;i++){
    tmp=buffer[i];
    if(write(sockfd,&tmp, sizeof(int))<0){
        error("error writing to the socket");
        pthread_exit(NULL);
      }
    }

  pthread_exit(NULL);

}

void *listenerthread8002(){

  printf("starting listener thread 2\n" );

  openSocket(8002);
  //newsockfds is stored in sockfds[5]


  int* buffer = malloc(sizeof(int)*(n*n));
  int sockfd=sockfds[7];

  //sockfd is the value our socket is reading and writing from
  //printf("sockfd is open at %d\n",sockfd);
  int i,tmp;
  for(i=0;i<n*n;i++){
    if(read(sockfd,&tmp, sizeof(int))<0){
      error("error reading from the socket");
      pthread_exit(NULL);
    }
    buffer[i]=tmp;
  }

  int solution [9][9];

  copyboard(solution, to9x9array(buffer));
  solve(solution,0,0);

  buffer = to81array(solution);

  for(i=0;i<n*n;i++){
    tmp=buffer[i];
    if(write(sockfd,&tmp, sizeof(int))<0){
        error("error writing to the socket");
        pthread_exit(NULL);
      }
    }

  pthread_exit(NULL);
}

void *listenerthread8003(){

  printf("starting listener thread 3\n" );

  openSocket(8003);


  int* buffer = malloc(sizeof(int)*(n*n));
  int sockfd=sockfds[8];

  //sockfd is the value our socket is reading and writing from
  //printf("sockfd is open at %d\n",sockfd);
  int i,tmp;
  for(i=0;i<n*n;i++){
    if(read(sockfd,&tmp, sizeof(int))<0){
      error("error reading from the socket");
      pthread_exit(NULL);
    }
    buffer[i]=tmp;
  }

  int solution [9][9];

  copyboard(solution, to9x9array(buffer));
  solve(solution,0,0);

  buffer = to81array(solution);

  for(i=0;i<n*n;i++){
    tmp=buffer[i];
    if(write(sockfd,&tmp, sizeof(int))<0){
        error("error writing to the socket");
        pthread_exit(NULL);
      }
    }

  pthread_exit(NULL);
}

void *listenerthread8004(){

  printf("starting listener thread 4\n" );

  openSocket(8004);

  int* buffer = malloc(sizeof(int)*(n*n));
  int sockfd=sockfds[9];

  //sockfd is the value our socket is reading and writing from
  //printf("sockfd is open at %d\n",sockfd);
  int i,tmp;
  for(i=0;i<n*n;i++){
    if(read(sockfd,&tmp, sizeof(int))<0){
      error("error reading from the socket");
      pthread_exit(NULL);
    }
    buffer[i]=tmp;
  }

  int solution [9][9];

  copyboard(solution, to9x9array(buffer));

  if(isValid(solution))
    solve(solution,0,0);

  buffer = to81array(solution);

  for(i=0;i<n*n;i++){
    tmp=buffer[i];
    if(write(sockfd,&tmp, sizeof(int))<0){
        error("error writing to the socket");
        pthread_exit(NULL);
      }
    }


  pthread_exit(NULL);
}


//solves a sudoku puzzle
int solve(int board[][n], int row, int col){
    int val;
    if(row>=9 || col>=9)
      return 1;

    //if the board has a value at row,col
    if(board[row][col] != 0){
        if((col+1)<9)
          //recurse on the next col if there is one
          return solve(board, row, col+1);
        if((row+1)<9)
          //recurse on the next row if there is one
          return solve(board, row+1, 0);
        //there is neither another row or col, ie the board is full
        else return 1;
    }

    //this row,col is blank (contains 0)
    //for every value that is acceptable in this spot
    for(val=1; val<=9; val++){

      if(isAvailable(board, row, col, val)){
        board[row][col] = val;
        //if we have another col to check
        if((col+1)<9){
          //recurse on the next col with this value here
          if(solve(board, row, col +1))
            return 1;
          else
          //didn't work so we backtrack
            board[row][col] = 0;
        }
        else
        //if there's another row
          if((row+1)<9){
            //using this value recurse and see if it works
            if(solve(board, row+1, 0))
              return 1;
            //didn't work so backtrack
            else
              board[row][col] = 0;
          }

      //there's no more rows or cols
      //else
        //return 1;
      }//end isAvailable

    }//end for loop
  //if we're out of places to put values and there's no
  //values that work, then solving was unsuccessful
  return 0;
}


void launchListenerThreads(){
  pthread_create(&listenerthreads[0], NULL, &listenerthread8000, NULL);
  pthread_create(&listenerthreads[1], NULL, &listenerthread8001, NULL);
  pthread_create(&listenerthreads[2], NULL, &listenerthread8002, NULL);
  pthread_create(&listenerthreads[3], NULL, &listenerthread8003, NULL);
  pthread_create(&listenerthreads[4], NULL, &listenerthread8004, NULL);
}

void forcecloseListenerThreads(pthread_t listenerthreads[5]){
  int i;
  for(i=0;i<5;i++){
    pthread_cancel(listenerthreads[i]);
  }
}


void closeListenerThreads(pthread_t listenerthreads[5]){
    int i;
    for(i=0;i<5;i++){
      pthread_join(listenerthreads[i],NULL);
    }

}


int main(int argc, char const *argv[]) {

  //launches listener threads
  launchListenerThreads();

  //wait for the listener threads to each get their puzzle, solve it,
  //and send back a solution
  //should block here and solve boards
  closeListenerThreads(listenerthreads);


  closeSockets(sockfds);


  return 0;
}
