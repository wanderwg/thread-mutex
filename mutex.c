#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex;
int ticket=100;
void* yellow_bull(void* arg)
{
    while(1)
    {
        //pthread_mutex_lock(pthread_mutex_t* _mutex)
        pthread_mutex_lock(&mutex);
        if(ticket>0){
            usleep(1000);
            printf("bull %d get the ticket:%d\n",(int)arg,ticket);
            ticket--;
        }
        else{
            printf("have no ticket,bull %d exit\n",(int)arg);
            //用户在加锁之后，需要在任意有可能退出线程的地方进行解锁
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&mutex);
    }

}
int  main()
{
    pthread_t tid[4];
    //int pthread_mutex_init(pthread_mutex_t *mutex,pthread_mutexattr_t *attr);
    pthread_mutex_init(&mutex,NULL);
    int i;
    for(i=0;i<4;++i)
    {
        int ret=pthread_create(&tid[i],NULL,yellow_bull,(void*)i);
        if(ret!=0){
            printf("thread create error!\n");
            return -1;
        }
    }
    for(i=0;i<4;++i)
    {
        pthread_join(tid[i],NULL);
    }
    //int pthread_mutex_destroy(pthread_mutex_t *mutex);
    pthread_mutex_destroy(&mutex);
    return 0;
}
