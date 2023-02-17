#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "pthread.h"
#include <unistd.h>

typedef struct attrs{
    int id;
    bool is_working;
} attrs_t;

void* proc(void* args){
    int *ret = (int*)malloc(sizeof(int));
    attrs_t *arg = (attrs_t*) args;
    printf("Поток %d стартовал\n", arg->id);
    while (arg->is_working)
    {
        printf("Поток %d работает\n", arg->id);
        fflush(stdout);
        sleep(1);
    }
    *ret = rand();
    printf("Поток %d завершил работу\n",arg->id);
    pthread_exit(ret);
};


int main()
{
    pthread_t thread1;
    pthread_t thread2;
    attrs_t args1,args2;
    args1.id = 1;
    args1.is_working = true;
    args2.id = 2;
    args2.is_working = true;
    int *status1, *status2;
    printf("Основной поток стартовал\n");
    pthread_create(&thread1,NULL,proc, &args1);
    pthread_create(&thread2,NULL,proc, &args2);
    getchar();
    printf("Клавиша нажата\n");
    args1.is_working= false;
    args2.is_working = false;
    pthread_join(thread1,(void**)&status1);
    printf("exit code - %p\n",status1);
    pthread_join(thread2,(void**)&status2);
    printf("exit code - %p\n",status2);
    free(status1);
    free(status2);
    printf("Основной поток завершил работу\n");

    return 0;
}
