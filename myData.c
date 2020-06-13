#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ_END 0 //Defined READ_END Tunel(fd[]) index
#define WRITE_END 1// Defined WRITE_END Tunel(fd[]) index

void pipeCreate();
void printErrorMessage(char *errorMessage);
/* 
*argv[] has two cases, 
one of C File Name who is full reads input file texts, and Txt File Name 
another of C File Name who is reads input file texts, Txt File Name, '=' operator and Another C File Name who is reads by paging input file texts
*/
int main(int argc, char *argv[]) {

  FILE *fp;
  char dataFromTXT[9999];
  fp = fopen(argv[1],"r"); // File opening in read-only mode
  
  if(fp == NULL){//Control for file exits.
    printErrorMessage("File can not open");
    exit(1);
  }

  fread(dataFromTXT, sizeof(char),sizeof(dataFromTXT),fp);//File reading...
  
  switch(argc)//argument count
  {

    case 2:
    { //If argument count 2
      printf("%s",dataFromTXT); //All texts printing.
      break;
    }

    case 4:
    { //If argument count 4
      
      if(*argv[2] != '=')
      {
        printf("You entered wrong operator");
        break;
      }
      
      int fd[2]; //Tunel defined.
      pid_t pid; //Process defining.

      pipeCreate(fd);//Pipe creating.

      pid = fork();//Fork process (creating pid>0 parent and pid=0 child process)
      if(pid < 0)
        printErrorMessage("Fork Failed");

      if(pid > 0)//Parent process
      {
        /* close the unused end of the pipe */
        close(fd[READ_END]);
        /* write to the pipe */
        printf("Parent process writing to pipe...\n");
        write(fd[WRITE_END],dataFromTXT,strlen(dataFromTXT)+1);
        printf("Parent process wrote to pipe.\n");
        /* close the write end of the pipe */
        close(fd[WRITE_END]);
        wait(NULL);
        printf("Parent process end.\n");
      }
    
      else
      { 
        char programDefinitionString[] = "./";
        strncat(programDefinitionString, argv[3], sizeof(argv[3])); 
        char *args[]={programDefinitionString,NULL}; 
        printf("Executing myMore.c ...\n");
        execv(args[0],args);
      }
      
      break;
    }

    default:
    {
      printf("You entered wrong value");
      break;
    }
  }
  return 0;
}

void pipeCreate(int fd[]){
  // create the pipe
  if(pipe(fd)==-1)
    printErrorMessage("Pipe failed");
  else
    printf("\nPipe Created!\n");
}

void printErrorMessage(char *errorMessage){
  fprintf(stderr,"%s",errorMessage);
  sleep(3);
  exit(1);
}
