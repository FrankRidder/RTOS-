#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t wait_mutex;
void section_1() {

    pthread_mutex_lock(&wait_mutex);
    for (int i = 0; i < 5; ++i) {
        printf("section 1\n");
        sleep(1);
    }
    pthread_mutex_unlock(&wait_mutex);

}

void section_2() {

    pthread_mutex_lock(&wait_mutex);
    for (int i = 0; i < 5; ++i) {
        printf("section 2\n");
        sleep(1);
    }
    pthread_mutex_unlock(&wait_mutex);

}

int main() {
    pthread_t thread1;
    pthread_t thread2;

    pthread_mutex_init(&wait_mutex, NULL);

    pthread_create(&thread1, NULL, (void *) section_1, NULL);
    sleep(2);
    pthread_create(&thread2, NULL, (void *) section_2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    pthread_mutex_destroy(&wait_mutex);

    return 0;
}