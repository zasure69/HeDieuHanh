#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <time.h>

/* the size (in bytes) of shared memory object */
const int SIZE = 10;

struct buffer {
    int data[10];
    int cnt;
};

int main() {
    /* name of the shared memory object */
    const char *name = "bounded-buffer";
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory object */
    struct buffer *ptr;
    /* create the shared memory object */
    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);
    /* memory map the shared memory object */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ptr->cnt = 0;
    pid_t pid = fork();
    if (pid > 0) {
        // Producer process
        srand(time(0));
        int sum = 0;
        while (sum <= 100) {
            int random_number = rand() % 11 + 10;
            while (ptr->cnt == 10) {};
            ptr->data[ptr->cnt] = random_number;
            ptr->cnt++;
            sum += random_number;
            printf("Produced: %d\n", random_number);
        }
        wait(NULL);
        printf("Producer process finished.\n");
        // Unmap the shared memory segment and close the file descriptor
        munmap(ptr, SIZE);
        close(fd);
        // Remove the shared memory segment
        shm_unlink(name);
    } else if (pid == 0) {
        // Consumer process
        int sum = 0;
        while (sum <= 100) {
            while (ptr->cnt == 0) {};
            int num = ptr->data[ptr->cnt - 1];
            ptr->cnt--;
            sum += num;
            printf("Consumed: %d\n", num);
        }
        printf("Consumer process finished. Total sum: %d\n", sum);
    }
    return 0;
}
