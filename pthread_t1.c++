#include<iostream>
#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<pthread.h>

#define TIMEOUT_SEC 5

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    unsigned count;
}
bosal_sem_t;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


int condition_met = 0; 

void *thread_function(void *arg){
    struct timespec timeout;
    struct timeval now;
    int rc;
    int msec=1;

    pthread_mutex_lock(&mutex);

    while(!condition_met){
        // gettimeofday(&now,NULL);
        // timeout.tv_sec = now.tv_sec + TIMEOUT_SEC;
        // timeout.tv_nsec = now.tv_usec*1000;
        struct timespec tspec = {msec/1000, (msec%1000)*1000000 } ;

        rc = pthread_cond_timedwait(&cond, &mutex, &tspec);

        if(rc==ETIMEDOUT){
            std::cout<<"Timeout occured"<<std::endl;
            break;
        }
        else if(rc!=0){
            perror("pthread_cond_timeout");
            break;
        }

    }

    
    if (condition_met){
        std::cout<<"Condition met by another thread."<<std::endl;
    }
    
    pthread_mutex_unlock(&mutex);
    return NULL;
    

}


int main(){

    

    pthread_t thread;
    pthread_create(&thread,NULL, thread_function, NULL);
    sleep(2);
    std::cout<<"Mutex : "<<&mutex<<std::endl;
    // std::cout<<"cond : "<<cond<<std::endl;
    pthread_mutex_lock(&mutex);
    condition_met = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);
    pthread_join(thread,NULL);


    return 0;
}