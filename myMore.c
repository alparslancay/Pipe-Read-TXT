#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) 
{ 
  int fd[2] = {atoi(argv[1]),atoi(argv[2])};

  printf("%d",fd[0]);
  printf("%d",fd[1]);
  char read_msg[9999];
  /* child process */
    /* close the unused end of the pipe */
    close(fd[WRITE_END]);
    /* read from the pipe */
    read(fd[READ_END],read_msg,9999);
    printf("Child proses pipe'dan okudu: %s\n",read_msg);
    /* close the write end of the pipe */
    close(fd[READ_END]);
  return 0; 
} 
