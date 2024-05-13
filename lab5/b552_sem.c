#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>

sem_t sem1, sem2, sem3;
int n, size;
int *a;

void *push() {
    srand(time(NULL));
    while(1) {
        sem_wait(&sem2);
        sem_wait(&sem3);
        a[size] = rand() % 100 + 1;
        size++;
        printf("Push: %d\n", a[size-1]);
        printf("Size of a after push: %d\n", size);
        sem_post(&sem3);
        sem_post(&sem1);
    }
}

void *pop() {
    while(1) {
        sem_wait(&sem1);
        sem_wait(&sem3);
        size--;
        printf("Pop: %d\n", a[size]);
        if (size) 
            printf("Size of a after pop: %d\n", size);
        else 
            printf("Nothing in array a\n");
        sem_post(&sem3);
        sem_post(&sem2);
    }
}


int main() {
    printf("Enter size of array n: ");
    scanf("%d", &n);
    a = (int*) malloc(n * sizeof(int));

    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, n);
    sem_init(&sem3, 0, 1);

    pthread_t t1, t2;
    
    pthread_create(&t1, NULL, push, NULL);
    pthread_create(&t2, NULL, pop, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}