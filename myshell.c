#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "LineParser.h"

void execute(cmdLine *pCmdLine){
  int ret, pid;
  pid = fork();
  if (pid==-1){
   perror("fork"); 
  }
  else if (pid==0){
    ret = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
    if (ret==-1){
     perror("failed to execute command"); 
     _exit(1);
    }
    _exit(0);
  }
  
    wait(pid);
  
 }
 
int main(int argc, char *argv[]){
 char path[PATH_MAX];
 char command[MAX_CMD_SIZE];
 cmdLine *current_command; 
 
 printf("Welcome to MyShell - A simple linux shell emulator.\n");
   do{
   getcwd(path,PATH_MAX);
   printf("%s$ ",path);
   fgets(command, MAX_CMD_SIZE , stdin);
   current_command = parseCmdLines(command);
   if (strcmp(current_command->arguments[0],"quit")==0){
     printf("bye bye...\n");  
     break;
   }
   execute(current_command);
   }while(1);

 
 
 
 return 0;
}