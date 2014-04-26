#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include "LineParser.h"
#define MAX_LOG_SIZE 10

void add_to_log(char *cmd,int *cLog_address,char *log_history[]){
  log_history[*cLog_address] = (char*)malloc(strlen(cmd));
  strcpy(log_history[*cLog_address], cmd);
  if (*cLog_address == MAX_LOG_SIZE-1){
    *cLog_address = 0;
  }
  else{
    (*cLog_address)++;
  }
}

void print_log(int cLog,char *log_history[]){
  int i;
  i = 0;
  do{
    if (i == 10){
     break; 
    }
    if (log_history[cLog] !=0){
    printf("%s",log_history[cLog]);
    }
    cLog++;
    if (cLog==MAX_LOG_SIZE){
     cLog = 0; 
    }
    i++;
    
    
  }while(1);
    
}

void execute(cmdLine *pCmdLine){
  int ret, pid, c_status;
  pid = fork();
  if (pid==-1){
   perror("fork"); 
  }
  else if (pid==0){
    ret = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
    if (ret==-1){
     perror("failed to execute command"); 
     _exit(0);
   }
  }
       if (pCmdLine->blocking==1){
	waitpid(-1,&c_status,0);
	}
   }
 
int main(int argc, char *argv[]){
 
 /*local variables declaration*/
 char path[PATH_MAX];
 char command[MAX_CMD_SIZE];
 char *log_history[MAX_LOG_SIZE];
 cmdLine *current_command; 
 int ret,cLog,i;

 
 
 /*local variables assignment*/
 cLog = 0;
 for (i=0; i<MAX_LOG_SIZE; i++){
     log_history[i]=0; /*initialize in order to know what to free later*/
 }
 
 
 printf("Welcome to Shell.\n");
   do{
   getcwd(path,PATH_MAX);
   printf("%s$ ",path);
   fgets(command, MAX_CMD_SIZE , stdin);
   current_command = parseCmdLines(command);
   if (current_command == 0) {
     continue; /*empty input*/
   }
   add_to_log(command,&cLog,log_history);
   if (strcmp(current_command->arguments[0],"quit")==0){
     /*quit code*/
     printf("bye bye...\n");
     freeCmdLines(current_command);
     break;
   }
   else if (strcmp(current_command->arguments[0],"cd")==0){
    /*cd code*/
    if (current_command->argCount==1){ /*no args were given*/
      printf("cd: please specify a path.\n");
    }
    else{
     ret = chdir(current_command->arguments[1]); 
     if (ret == -1){
       perror(current_command->arguments[1]);
    }
    }
    freeCmdLines(current_command);
   }
   else if (strcmp(current_command->arguments[0],"assign")==0){
    /*assign code*/
    
    freeCmdLines(current_command);
   
   }
   else if (strcmp(current_command->arguments[0],"unassign")==0){
    /*unassign code*/
    
    freeCmdLines(current_command);
    
   }
   else if (strcmp(current_command->arguments[0],"env")==0){
    /*env code*/
    
    freeCmdLines(current_command);
    
   }
   else if (strcmp(current_command->arguments[0],"log")==0){
    /*log code*/
    
    print_log(cLog,log_history);
    freeCmdLines(current_command);
    
   }
   else{ 
    execute(current_command);
    freeCmdLines(current_command);
   }
   }while(1);
    for (i=0; i<MAX_LOG_SIZE; i++){
     if (log_history[i]!=0){
      free(log_history[i]); 
     }
    }
    
return 0;
}
