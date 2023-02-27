#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){
    pid_t pid = fork();
    int exit_code;
    if (pid == 0){
        printf("message_from_%d_process{\n\tРодительский процесс - %d\n\tДочерний процесс - %d (стартовал)\n}\n", getpid(), getppid(), getpid());
        for (int i = 0; i < argc; i++){
            printf("%s\n", argv[i]);
            fflush(stdout);
            sleep(1);
        }
    }else if (pid > 0){
        printf("message_from%d_process{\n\tРодительский процесс\n}\n", getpid());
        fflush(stdout);
    }else{
        perror("fork");
        fflush(stdout);
    }
    printf("message_from%d_process{\n\tПроцесс %d звершил работу с кодом %d\n}\n", getpid(), getpid(),exit_code);
    fflush(stdout);
    return 0;
}