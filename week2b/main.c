/* Includes */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SEND_BUFFER 70

/* Threads */
static void *MainThread();

static void *AnotherThread();

/* Defines */
pthread_mutex_t wait_mutex;

int p[2], i;

int main(void) {
    pthread_t mainThread, anotherThread;

    if (pipe(p) < 0) {
        return 0;
    }

    printf("Creating threads .. \n");

    if (pthread_mutex_init(&wait_mutex, NULL) != 0) {
        printf("\n mutex init has failed\n");
        return 1;
    }

    pthread_create(&mainThread, NULL, &MainThread, NULL);

    pthread_create(&anotherThread, NULL, &AnotherThread, NULL);

    pthread_join(mainThread, NULL);

    pthread_join(anotherThread, NULL);

    pthread_mutex_destroy(&wait_mutex);

    return 0;
}


/* Main thread .. Waiting for messages */
static void *MainThread() {
    char buffer[MAX_SEND_BUFFER];
    int bytes_read;

    printf("[MainThread] Inside main thread \n");

    // Let the other thread wait till I am ready!
    pthread_mutex_lock(&wait_mutex);

    // Clear the buffer
    memset(buffer, 0, MAX_SEND_BUFFER);

    // Detach the thread
    pthread_detach(pthread_self());

    printf("[MainThread] Waiting for messages ... \n");
    pthread_mutex_unlock(&wait_mutex);

    for (int count = 0; count < 50; count++) {
        bytes_read = read(p[0], buffer, MAX_SEND_BUFFER);;

        if (bytes_read == -1) {
            perror("[MainThread] Failed to recieve:");
            return 0;
        } else {
            printf("[MainThread] Data %d: %s \n", count + 1, buffer);

            memset(buffer, 0, MAX_SEND_BUFFER);
        }
    }
    return 0;
}

static void *AnotherThread() {
    pthread_mutex_lock(&wait_mutex);
    printf("Inside second thread \n");

    char buffer[MAX_SEND_BUFFER];
    int count;

    for (count = 0; count < 50; count++) {

        int rint = rand() % 100 + 1;

        snprintf(buffer, MAX_SEND_BUFFER, "%d", rint);

        write(p[1], buffer, MAX_SEND_BUFFER);

    }

    printf("Done second thread \n");
    pthread_mutex_unlock(&wait_mutex);
    return 0;
}