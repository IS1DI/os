#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char **argv){
    int exit_code = 0;
        printf("message_from_%d_process{\n\tРодительский процесс - %d\n\tДочерний процесс - %d (стартовал)\n}\n", getpid(), getppid(), getpid());
        for (int i = 0; i < argc; i++){
            printf("message_from_%d_process{\n\t%s\n\n}\n",getpid(), argv[i]);
            fflush(stdout);
            sleep(1);
        }
    
    printf("message_from%d_process{\n\tПроцесс %d звершил работу с кодом %d\n}\n", getpid(), getpid(),exit_code);
    exit(exit_code);
}