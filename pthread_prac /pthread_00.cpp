//to compile g++ -std=c++17  pthread_00.cpp  -o main -lpthread
#include <stdio.h>
#include <time.h>
#include <errno.h>
#include<pthread.h>
#include<unistd.h>
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int done = 0;

void* thread_func(void* arg){

    struct timespec timeout;
    int ret;
    //lock mutex before waiting
    pthread_mutex_lock(&mutex);
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec +=5;
    while(done==0){
        printf("thread waiting on condition.\n");
        ret = pthread_cond_timedwait(&cond, &mutex, &timeout);
        if(ret==ETIMEDOUT){
            printf("Timeout Error.\n");
            break;
        }
        else if(ret!=0){
            printf("pthread_cond_timedwait error.\n ");
            break;
        }
    }
    if(done){
        printf("condition satisfies.\n");
    }

    //unlock mutex after waiting completed
    pthread_mutex_unlock(&mutex);
    return NULL;

}

int main(){
    pthread_t tid;

    pthread_create(&tid, NULL, thread_func,NULL);
    sleep(3);
    
    pthread_mutex_lock(&mutex);
    done=1;
    printf("main thread signaling condition.\n");
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    pthread_join(tid, NULL);
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;

}