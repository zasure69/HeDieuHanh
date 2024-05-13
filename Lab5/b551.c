#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

//Định nghĩa biến sem
sem_t sem1; 
sem_t sem2;
sem_t sem3;
    
int products, sells;

void *processA() {
    while(1) {
        sem_wait(&sem1);
        sem_wait(&sem3);
        sells++;
        printf("sells: sells = %d, products = %d, products-sell = %d\n", sells, products, products-sells);
        sem_post(&sem3);
        sem_post(&sem2);
        
    }
    pthread_exit(NULL);
}

void *processB() {
    while(1) {
        sem_wait(&sem2);
        sem_wait(&sem3);
        products++;
        printf("products: sells = %d, products = %d, products-sell = %d\n", sells, products, products-sells);
        sem_post(&sem3);
        sem_post(&sem1);
        
    }
    pthread_exit(NULL);
}


int main () {
    
    products = 0;
    sells = 0;
    //Biến sem có giá trị ban đầu pshared = 0 và value = 0
    sem_init(&sem1, 0, 0); 
    sem_init(&sem2, 0, 410);
    sem_init(&sem3, 0, 1);
    pthread_t t1, t2;

    pthread_create(&t1, NULL, processA, NULL);
    pthread_create(&t2, NULL, processB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_exit(NULL);
    return 0;
    
}