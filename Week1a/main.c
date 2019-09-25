#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *taskOne() {
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 1 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodater een aantal keer een context
switch naar taak 2 optreedt */
            }
        }
    }
}

void *taskTwo() {
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 2 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 4 optreedt */
            }
        }
    }
}

void *taskThree() {
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 3 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 4 optreedt */
            }
        }
    }
}

void *taskFour() {
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 4 %i\n", j);
                for (m = 0; m <= 1000; m++)
                    for (n = 0; n <= 10000; n++);
/* De for-lussen dienen om een vertraging te
realiseren, zodat er een aantal keer een context
switch naar taak 3 optreedt */
            }
        }
    }
}


int main() {
    long i = 0;
    int status = 0;

    pthread_t threads[4];
    pthread_attr_t tattr;
    pthread_attr_init(&tattr);//tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR); //sched policy aanpassen

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
    status = pthread_create(&threads[2], &tattr, taskThree, (void *) i);    //Create threads
    if (status != 0) {
        printf("While creating thread 3, pthread_create returned error code %d\n", status);
        exit(-1);
    }
    status = pthread_create(&threads[3], &tattr, taskFour, (void *) i);    //Create threads
    if (status != 0) {
        printf("While creating thread 4, pthread_create returned error code %d\n", status);
        exit(-1);
    }

    pthread_exit(NULL);
}
