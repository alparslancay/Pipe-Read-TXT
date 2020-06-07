#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]) {
  FILE *fp;
  char dataFromTXT[9999];
  fp = fopen("inputFile.txt","r");
  
  fread(dataFromTXT, sizeof(char),sizeof(dataFromTXT),fp);
  
  switch(argc){

  case 1:{
    printf("%s",dataFromTXT);
    break;
  }

  case 3:{

    if(fp == NULL){
      printf("File can not open");
      exit(1);
    }

    else{

      int fd[2];
      pid_t pid;
      /* create the pipe */
      if(pipe(fd)==-1)
      {
        fprintf(stderr,"Pipe failed");
        return 1;
      }
      /* fork a child process */
      pid = fork();
      if(pid < 0)
      {/* error occurred */
        fprintf(stderr,"Fork Failed");
      return 1;
      }

      if(pid > 0)
      { /* parent process */
        /* close the unused end of the pipe */
        close(fd[READ_END]);
        /* write to the pipe */
        write(fd[WRITE_END],dataFromTXT,strlen(dataFromTXT)+1);
        printf("Parent proses pipe'a yazdı...\n");
        /* close the write end of the pipe */
        close(fd[WRITE_END]);
        wait(NULL);
        printf("Parent proses sonlandı...\n");
      }
      
      else
      { 
        /*char *argsChar[2];
        sprintf(argsChar[0], "%d", fd[0]);
        sprintf(argsChar[1], "%d", fd[1]);*/

        char *args[]={argv[2],NULL}; 
        execv(args[0],args);
        printf("Child proses sonlandı...\n");
      }

    }
    
    break;
  }

  default:{
    printf("You entered wrong value");
    break;
  }
  
  }
  return 0;
}
