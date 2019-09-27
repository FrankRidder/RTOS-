#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *taskOne() {
    int j =0;
    struct timespec tim;
    tim.tv_sec  = 0;
    tim.tv_nsec = 500000000L;
    while (1) {
        nanosleep(&tim,NULL);
        j++;
        printf("taak 1 %i\n", j);
    }
}

void *taskTwo() {
    int j = 0;
    struct timespec tim;
    tim.tv_sec  = 1;
    tim.tv_nsec = 300000000L;
    while (1) {
        nanosleep(&tim,NULL);
        j++;
        printf("taak 2 %i\n", j);
    }
}


int main() {
    long i = 0;
    int status = 0;

    pthread_t threads[2];
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);//tattr init met defaultwaarden

    status = pthread_create(&threads[0], &tattr, taskOne, (void *) i);    //Create threads
    if (status != 0) {
        printf("While creating thread 1, pthread_create returned error code %d\n", status);
        exit(-1);
    }
    status = pthread_create(&threads[1], &tattr, taskTwo, (void *) i);    //Create threads
    if (status != 0) {
        printf("While creating thread 2 pthread_create returned error code %d\n", status);
        exit(-1);
    }
    pthread_exit(NULL);
}
