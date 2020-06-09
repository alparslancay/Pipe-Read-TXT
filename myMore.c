#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define READ_END 0 //Defined READ_END Tunel(fd[]) index
#define WRITE_END 1// Defined WRITE_END Tunel(fd[]) index


int currentIndex = -1;//Defined currentIndex for read.
char read_msg[9999];//Defined message index.

void read24Lines();
char getAnswer();
void dispose();

int isOver = 0;

int main(int argc, char *argv[]) 
{ 
  int fd[2] = {4,5}; //Defined using tunel numbers.

  /* child process */
  /* close the unused end of the pipe */
  close(fd[WRITE_END]);
  /* read from the pipe */
  read(fd[READ_END],read_msg,9999);
  /* close the write end of the pipe */
  close(fd[READ_END]);

  char choice =' '; //Choice defined.
  
  read24Lines();//Reading first 24 lines.

  while(!isOver)//While until it is over
  {

    choice = getAnswer();

    if(choice == ' ')
      read24Lines();
    
    if(choice == 'q')
      break;
  }
  printf("\nmyMore.c end\n");
  return 0; 
}

void read24Lines(){

  char currentChar;
  printf("\n\n----Text Reading---- \n\n");
  sleep(1);
  int currentReadLines = 0;

  while(currentReadLines < 24){
    currentChar = read_msg[currentIndex++];

    if(read_msg[currentIndex+1] == '\0')//Next character empty control
    {
      printf("\n\nAll texts read!\n\n");
      dispose();
      break;
    }
    printf("%c",currentChar);

    if(currentChar == '\n')//last character in current line control.
      currentReadLines++;
  }
  printf("\n");
}

char getAnswer(){

  char answer;
  printf("For continue enter ' ' (space) value, for exit enter 'q' value:\n");
  scanf("%c",&answer);

  return answer;
}

void dispose(){//For closing this c file.
  isOver = 1;
}

