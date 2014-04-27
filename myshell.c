#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>
#include "LineParser.h"
#define MAX_LOG_SIZE 10



void add_to_log(char *cmd, int *log_count, int *log_current, char *log_history[]){
  log_history[*log_current] = (char*)malloc(strlen(cmd)+1);
  strcpy(log_history[*log_current], cmd);
  *log_current = ((*log_current)+1)%MAX_LOG_SIZE;
  if (*log_count<10){
   (*log_count)++;
  }
  }

void print_log(int log_current,char *log_history[]){
  int i,exist;
  i = 0;
  exist = 0;
  do{
    if (i == MAX_LOG_SIZE){
     break; 
    }
    if (log_history[log_current] !=0){
    printf("%i: %s",exist,log_history[log_current]);
    exist++;
    }
    log_current = (log_current+1)%MAX_LOG_SIZE;
    i++;
  }while(1);
}

char *get_n_log(int log_count, int log_current,char *log_history[], int n){
  int oldest;
  if (log_count<10){
   oldest = 0; 
  }
  else{
   oldest = log_current-1;
  }
  return log_history[(oldest+n)%MAX_LOG_SIZE];
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
 int ret,i,num,log_count,log_current;

 
 
 /*local variables assignment*/
 log_current = 0;
 log_count = 0;
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
   if (*current_command->arguments[0]=='!'){
    /*"!" code*/
    num = atoi(1+(current_command->arguments[0]));
    if ((num>=MAX_LOG_SIZE)||(num == 0 && (*(1+(current_command->arguments[0]))!='0'))){
      printf("log: Please enter a number from 0 to %i.\n",MAX_LOG_SIZE-1);
    }
    strcpy(command,get_n_log(log_count,log_current,log_history,num));
    freeCmdLines(current_command);
    current_command = parseCmdLines(command);
    }
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
    
   }
   else if (strcmp(current_command->arguments[0],"assign")==0){
    /*assign code*/
    
    
   
   }
   else if (strcmp(current_command->arguments[0],"unassign")==0){
    /*unassign code*/
    
   
    
   }
   else if (strcmp(current_command->arguments[0],"env")==0){
    /*env code*/

   }
   else if (strcmp(current_command->arguments[0],"log")==0){
    /*log code*/
    print_log(log_current,log_history);  
   }
   else{ 
    execute(current_command);
   }
   
   freeCmdLines(current_command);
   add_to_log(command,&log_count,&log_current,log_history);
   }while(1);
    for (i=0; i<MAX_LOG_SIZE; i++){
     if (log_history[i]!=0){
      free(log_history[i]); 
     }
    }
   
return 0;
}
