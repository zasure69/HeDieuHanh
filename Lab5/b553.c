#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

    
int x = 0;

void *processA() {
    while(1) {
        x++;
        if (x == 20) {
            x = 0;
        }
        printf("Process A: %d\n", x);
    }
    pthread_exit(NULL);
}

void *processB() {
    while(1) {
        x++;
        if (x == 20) {
            x = 0;
        }  
        printf("Process B: %d\n", x); 
    }
    pthread_exit(NULL);
}


int main () {
    
    
    pthread_t t1, t2;

    pthread_create(&t1, NULL, processA, NULL);
    pthread_create(&t2, NULL, processB, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_exit(NULL);
    return 0;
    
}
