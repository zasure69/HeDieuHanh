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

int main (int argc, char* argv[]) {
    if (argc < 2) {
    	printf("Usage: ./collatz <number>\n");
    	return 1;
    }
    int n = atoi(argv[1]);
    const int SIZE = 4096;
    /* name of the shared memory object */
    const char *name = "OS";
    /* shared memory file descriptor */
    int fd;
    /* pointer to shared memory obect */
    
    __pid_t pid = fork();
    int *ptr;
    /* create the shared memory object */
    fd = shm_open(name, O_CREAT | O_RDWR,0666);
    /* configure the size of the shared memory object */
    ftruncate(fd, SIZE);
    /* memory map the shared memory object */
    ptr = (int*) mmap(0, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);
    

    if (pid == 0) {
        //Child process
        /* write to the shared memory object */
        int cnt = 1;
        while(1) {
            *(ptr + cnt) = n;
            
            if (n == 1) {
                break;
            }
            cnt++;
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n = 3 * n + 1;
            }
        }
        *ptr = cnt;
    } else if (pid > 0) {
        wait(NULL);
        /* read from the shared memory object */
        int size = *ptr;
        for (int i = 1; i < size; i++) {
            printf("%d, ", *(ptr + i));
        }
        printf("1\n");
        //file descriptor
        munmap(ptr, SIZE);
        close(fd);
        // remove the shared memory segment
        shm_unlink(name);
    }
    exit(0);
}
