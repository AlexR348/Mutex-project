#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t lock;
int shared_data = 0;

void *writer(void *arg) {
    pthread_mutex_lock(&lock);
    shared_data = rand() % 100; // Write some random data
    printf("Writer Thread: Wrote %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *reader(void *arg) {
    sleep(1); // Ensure writer executes first
    pthread_mutex_lock(&lock);
    printf("Reader Thread: Read %d\n", shared_data);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, writer, NULL);
    pthread_create(&t2, NULL, reader, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
