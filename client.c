
/*
Mark Gross mag210
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
#include "sudokusolver.h"
  //needs this to get 9x9->81 and 81->9x9

//#define n 9


void error(const char *msg){
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    int board[81] ={0}; //unsolved board
    int solvedBoard[81] ={0}; //solved board sent back from server

    if (argc < 4) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0){
        error("ERROR opening socket");
        exit(0);
    }

    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    //read from input file, got from arg
    FILE *inputFile = fopen (argv[3], "r");
    //printf("%d\n",inputFile);
    if (inputFile <= 0) { //checks to make sure file exists
      printf("Could Not Open File\n");
      exit(0);
    }

    //parse from input file into board (input array)
    int i;
    for(i=0;i<81;i++){
      fscanf(inputFile,"%1d",&board[i]);
    }


    printf("input board is:\n");
    int tmp [9][9];
    copyboard(tmp,to9x9array(board));
    printBoard(tmp);
    fflush(stdout);

    fclose(inputFile);

    //write our board to the socket
    for(i=0;i<81;i++){
        //printf("writing to socket value of %d, i is %d\n",board[i],i);
        if(write(sockfd,&board[i],sizeof(int))<0){
             error("ERROR writing to socket");
             return -1;
        }
    }

    //read the solved board from the socket
    int temp;
    for(i=0;i<81;i++){
      if(read(sockfd,&temp, sizeof(int))<0){
        error("error reading from the socket");
      }
      solvedBoard[i]=temp;
    }



    int recieved [9][9];
    copyboard(recieved,to9x9array(solvedBoard));

    if (isSolvedBoard(recieved)){
      printf("one solution is:\n");
      printBoard(recieved);
      fflush(stdout);
    }
    else{
      printf("no solution found\n" );
    }

    close(sockfd);
    return 0;
}
