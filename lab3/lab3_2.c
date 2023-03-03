#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/wait.h>
#pragma GCC diagnostic ignored "-Wwrite-strings"


int main(int argc, char** argv){
    int exit_code = 0;
    
    printf("message_from_mainX%d_process{\n\tРодительский процесс - %d\n\tДочерний процесс - %d (стартовал)\n}\n", getpid(), getppid(), getpid());
    pid_t pid = fork();
    if(pid==-1){
        perror("fork");

        
    }else if(pid==0){
        char* args[] = {"./lab3_1","arg", "ls",NULL};
        execv("./lab3_1",args);
        
    }else{
        int code;
        while(waitpid(pid,&code,WNOHANG) ==0){
            printf("message_from_mainX%d_process{\n\tЖдём пока процесс %d завершит работу\n}\n",getpid(),pid);
            fflush(stdout);
            usleep(500000);
        
            
        }
        printf("message_from_mainX%d_process{\n\tПроцесс %d завершил рвботу с кодом %d\n}\n",getpid(),pid,code);
    
    }
    printf("message_from_mainX%d_process{\n\tПроцесс закончил работу c кодом %d\n}\n",getpid(),exit_code);
    exit(exit_code);
}