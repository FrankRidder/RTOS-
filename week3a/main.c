#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem;

void section_1() {

    sem_wait(&sem);
    for (int i = 0; i < 5; ++i) {
        printf("section 1\n");
        sleep(1);
    }
    sem_post(&sem);

}

void section_2() {

    sem_wait(&sem);
    for (int i = 0; i < 5; ++i) {
        printf("section 2\n");
        sleep(1);
    }
    sem_post(&sem);

}

int main() {
    pthread_t thread1;
    pthread_t thread2;

    sem_init(&sem, 0, 1);

    pthread_create(&thread1, NULL, (void *) section_1, NULL);
    sleep(2);
    pthread_create(&thread2, NULL, (void *) section_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    sem_destroy(&sem);
    return 0;
}