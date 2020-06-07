#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1


int currentIndex = -1;
char read_msg[9999];

void read24Lines();
char getAnswer();

int main(int argc, char *argv[]) 
{ 
  int fd[2] = {4,5};


  /* child process */
  /* close the unused end of the pipe */
  close(fd[WRITE_END]);
  /* read from the pipe */
  read(fd[READ_END],read_msg,9999);
  /* close the write end of the pipe */
  close(fd[READ_END]);

  char choice =' ';
  char enterPassing;

  while(1){
  
    if(choice == ' '){
      read24Lines();
    }
    if(choice == 'q'){
      break;
    }

    choice = getAnswer();

  }
  return 0; 
}

void read24Lines(){

  char currentChar;
  printf("\nOKUMA İŞLEMİ YAPILIYOR \n");
  sleep(1);
  int currentReadLines = 0;
  while(currentReadLines < 24){
    currentChar = read_msg[currentIndex++];
    printf("%c",currentChar);

    if(currentChar == '\n')
      currentReadLines++;
  }
  printf("\n");
}

char getAnswer(){
  char answer;
  printf("Devam için boşluk değeri girin, çıkmak için 'q' değeri girin:\n");
  scanf("%c",&answer);

  return answer;
}
