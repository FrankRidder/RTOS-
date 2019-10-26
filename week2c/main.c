/* Includes */
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>

struct Memory {
    int  data[50];
};

/* Threads */
static void *MainThread();
static void *AnotherThread();

/* Defines */
pthread_mutex_t wait_mutex;

int main(void) {
    pthread_t mainThread, anotherThread;

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

    return 1;
}

/* Main thread .. Waiting for messages */
static void *MainThread() {
    // Let the other thread wait till I am ready!
    pthread_mutex_lock(&wait_mutex);

    struct Memory  *ShmPTR;

    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(struct Memory), 0666 | IPC_CREAT);

    // Detach the thread
    pthread_detach(pthread_self());

    printf("[MainThread] Waiting for messages ... \n");
    pthread_mutex_unlock(&wait_mutex);

    // shmat to attach to shared memory
    ShmPTR = (struct Memory *) shmat(shmid, (void *) 0, 0);

    printf("[MainThread] Inside main thread \n");
    for (int count = 0; count < 50; count++) {
        printf("Data read from memory number %d : %d\n", count + 1, ShmPTR->data[count]);

    }
    //detach from shared memory
    shmdt(ShmPTR);
    // destroy the shared memory
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}

static void *AnotherThread() {
    printf("[Second] Inside Second thread \n");
    struct Memory  *ShmPTR;

    // ftok to generate unique key
    key_t key = ftok("shmfile", 65);

    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(struct Memory), 0666 | IPC_CREAT);

    // shmat to attach to shared memory
    ShmPTR = (struct Memory *) shmat(shmid, (void *) 0, 0);

    for (int count = 0; count < 50; count++) {
        int rint = rand() % 100 + 1;
        ShmPTR->data[count] = rint;

    }
    //detach from shared memory
    shmdt(ShmPTR);
    return 0;
}