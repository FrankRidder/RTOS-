#include <iostream>
#include <pthread.h>

int main() {
    pthread_attr_t tattr;
    pthread_attr_init(&tattr); //tattr init met defaultwaarden
    pthread_attr_setschedpolicy(&tattr, SCHED_RR); //sched policy aanpassen
    pthread_create(&tid, &tattr, taskOne, arg);
    pthread_create(&tid, &tattr, taskTwo, arg);
    pthread_create(&tid, &tattr, taskThree, arg);
    pthread_create(&tid, &tattr, taskFour, arg);
}


void *taskOne() {
    int i, j, m, n;
    while (1) {
        for (i = 0; i < 5; i++) {
            for (j = 1; j <= 8; j++) {
                printf("taak 1 %i\n", j)
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
                printf("taak 2 %i\n", j)
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