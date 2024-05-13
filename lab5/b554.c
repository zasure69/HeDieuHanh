#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex;
int x = 0;

void *processA() {
    while(1) {
        pthread_mutex_lock(&mutex);
        x++;
        if (x == 20) {
            x = 0;
        }
        printf("Process A: %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

void *processB() {
    while(1) {
        pthread_mutex_lock(&mutex);
        x++;
        if (x == 20) {
            x = 0;
        }
        printf("Process B: %d\n", x);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}


int main () {
    
    //Biến sem có giá trị ban đầu pshared = 0 và value = 0
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&t1, NULL, processA, NULL);
    pthread_create(&t2, NULL, processB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_exit(NULL);
    return 0;
    
}