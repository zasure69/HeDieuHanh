#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

int x1, x2, x3, x4, x5, x6;
int w, v, z, y, ans;
pthread_mutex_t mutex[6];

void *a() {
    w = x1 * x2;
    printf("Lệnh a: w = x1 * x2 = %d\n", w);
    pthread_mutex_unlock(&mutex[1]);
}

void *b() {
    v = x3 * x4;
    printf("Lệnh b: v = x3 * x4 = %d\n", v);
    pthread_mutex_unlock(&mutex[0]);
}

void *c() {
    pthread_mutex_lock(&mutex[0]);
    pthread_mutex_unlock(&mutex[0]);
    y = v * x5;
    printf("Lệnh c: y = v * x5 = %d\n", y);
    pthread_mutex_unlock(&mutex[2]);
    
}

void *d() {
    pthread_mutex_lock(&mutex[0]);
    pthread_mutex_unlock(&mutex[0]);
    z = v * x6;
    printf("Lệnh d: z = v * x6 = %d\n", z);
    pthread_mutex_unlock(&mutex[3]);
    
}

void *e() {
    pthread_mutex_lock(&mutex[1]);
    pthread_mutex_unlock(&mutex[1]);
    pthread_mutex_lock(&mutex[2]);
    y = w * y;
    printf("Lệnh e: y = w * y = %d\n", y);
    pthread_mutex_unlock(&mutex[4]);
}

void *f() {
    pthread_mutex_lock(&mutex[1]);
    pthread_mutex_unlock(&mutex[1]);
    pthread_mutex_lock(&mutex[3]);
    z = w * z;
    printf("Lệnh f: z = w * z = %d\n", z);
    pthread_mutex_unlock(&mutex[5]);
}

void *g() {
    pthread_mutex_lock(&mutex[4]);
    pthread_mutex_lock(&mutex[5]);
    ans = y + z;
    printf("Lệnh g: ans = y + z = %d\n", ans);
}

int main() {
    for (int i = 0; i < 6; i++) {
        pthread_mutex_init(&mutex[i], NULL);
        pthread_mutex_lock(&mutex[i]);
    }

    printf("Nhập các biến x1, x2, x3, x4, x5, x6: ");
    scanf("%d %d %d %d %d %d", &x1, &x2, &x3, &x4, &x5, &x6);

    pthread_t thread[7];
    
    pthread_create(&thread[0], NULL, a, NULL);
    pthread_create(&thread[1], NULL, b, NULL);
    pthread_create(&thread[2], NULL, c, NULL);
    pthread_create(&thread[3], NULL, d, NULL);
    pthread_create(&thread[4], NULL, e, NULL);
    pthread_create(&thread[5], NULL, f, NULL);
    pthread_create(&thread[6], NULL, g, NULL);

    pthread_join(thread[0], NULL);
    pthread_join(thread[1], NULL);
    pthread_join(thread[2], NULL);
    pthread_join(thread[3], NULL);
    pthread_join(thread[4], NULL);
    pthread_join(thread[5], NULL);
    pthread_join(thread[6], NULL);

    pthread_exit(NULL);

    return 0;
}