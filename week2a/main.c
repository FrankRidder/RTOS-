/* Includes */
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 10000
#define MAX_SEND_BUFFER 70
#define MAIN_QNAME "/MainQueue"
/* Threads */
static void *MainThread(void *);

static void *AnotherThread(void *);

/* Defines */

pthread_mutex_t wait_mutex;

int main(void) {
    pthread_t mainThread, anotherThread;


    printf("Creating threads .. \n");
    pthread_create(&mainThread, NULL, &MainThread, NULL);

    pthread_create(&anotherThread, NULL, &AnotherThread, NULL);

    pthread_mutex_init(&wait_mutex, NULL);


    pthread_join(mainThread, NULL);
    pthread_join(anotherThread, NULL);

    pthread_mutex_destroy(&wait_mutex);


    return 1;
}



/* Main thread .. Waiting for messages */
static void *MainThread(void *args) {

    mqd_t queue_handle;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    struct mq_attr msgq_attr;
    unsigned int sender;

    printf("[MainThread] Inside main thread \n");


    // Let the other thread wait till I am ready!
    pthread_mutex_lock(&wait_mutex);

    // Clear the buffer
    memset(buffer, 0, BUFFER_SIZE);


    // Detach the thread
    pthread_detach(pthread_self());

    // unlink the queue if it exisits - debug
    mq_unlink(MAIN_QNAME);


    printf("[MainThread]Opening MQ \n");
    queue_handle = mq_open(MAIN_QNAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);

    if (queue_handle == -1) {
        perror("[MainThread] Error Opening MQ: ");
        return 0;
    }

    printf("[MainThread] Waiting for messages ... \n");
    pthread_mutex_unlock(&wait_mutex);


    int amount_of_int = 1;

    for (;;) {
        bytes_read = mq_receive(queue_handle, buffer, BUFFER_SIZE, &sender);

        if (bytes_read == -1) {
            perror("[MainThread] Failed to recieve:");
            return 0;
        } else {
            printf("[MainThread] Data %d: %s \n",amount_of_int, buffer);
            amount_of_int++;
            // Get the MQ attributes
            mq_getattr(queue_handle, &msgq_attr);

            // Clear buffer and sleep to block for some time t and see
            // if you get all the messages!

            memset(buffer, 0, BUFFER_SIZE);
        }
    }

    mq_close(queue_handle);
}

static void *AnotherThread(void *args) {

    mqd_t queue_handle;
    char buffer[MAX_SEND_BUFFER];
    unsigned int msgprio = 1;

    int count;

    pthread_mutex_lock(&wait_mutex);


    queue_handle = mq_open(MAIN_QNAME, O_RDWR);
    if (queue_handle == -1) {

        perror("[AnotherThread] Error Opening MQ:");
        return 0;
    }

    for (count = 0; count < 50; count++) {

        int rint = rand() % 100 + 1;

        snprintf(buffer, MAX_SEND_BUFFER, "%d", rint);

        if (0 != mq_send(queue_handle, buffer, strlen(buffer) + 1, msgprio)) {

            perror("[AnotherThread] Sending:");
            mq_close(queue_handle);
            pthread_mutex_unlock(&wait_mutex);

            return 0;
        }
    }

    pthread_mutex_unlock(&wait_mutex);
    mq_close(queue_handle);


    return 0;
}