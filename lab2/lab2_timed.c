#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include <pthread.h>
#include <unistd.h>
#include <time.h>


pthread_mutex_t mutex;
typedef struct attrs{
    int id;
    bool is_working;
} attrs_t;


void* proc(void* args){
    attrs_t *arg = (attrs_t*) args;
    printf("Поток %d стартовал\n", arg->id);
    int* ret = (int*)malloc(sizeof(int)); 
    *ret = rand();
    struct timespec tme;
    while (arg->is_working)
    {
        int code;
        do{
            clock_gettime(CLOCK_REALTIME, &tme);
            tme.tv_sec += 1;
            code = pthread_mutex_timedlock(&mutex,&tme);
            if(code!=0){
                printf("\nerror - %d\n",sterror(code));
            }
        }while(code!=0);

        for (int i = 0; i < 10; i++)
        {
            
            printf("%d",arg->id);
            fflush(stdout);
            sleep(1);
        }
        
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    printf("Число rand = %d в %d потоке \nПоток %d завершил работу\n",*ret,arg->id, arg->id);
    pthread_exit(ret);
};  


int main()
{
    
    pthread_mutex_init(&mutex,NULL);
    pthread_t thread1;
    pthread_t thread2;
    attrs_t args1,args2;
    args1.id = 1;
    args1.is_working = true;
    args2.id = 2;
    args2.is_working = true;
    int *status1,*status2;
    printf("Основной поток стартовал\n");
    pthread_create(&thread1,NULL,proc, &args1);
    pthread_create(&thread2,NULL,proc, &args2);
    getchar();
    printf("Клавиша нажата\n");
    args1.is_working= false;
    args2.is_working = false;
    pthread_join(thread1,(void**)&status1);
    printf("Число rand = %d в main потоке, полученное из %d потока\n",*status1,args1.id);
    free(status1);
    pthread_join(thread2,(void**)&status2);
    printf("Число rand = %d в main потоке, полученное из %d потока\n",*status2,args2.id);
    free(status2);
    pthread_mutex_destroy(&mutex);
    printf("mutex удалён\n");
    printf("Основной поток завершил работу\n");
    return 0;
}