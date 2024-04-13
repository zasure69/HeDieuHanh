#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: ./time <command>\n");
        return 1;
    }

    struct timeval start, end;

    __pid_t pid = fork();
    gettimeofday(&start, NULL);

    if (pid == 0) {
        // Tiến trình con
        execl("/bin/sh", "sh", "-c", argv[1], NULL);
    } else {
        // Tiến trình cha
        wait(NULL);
        gettimeofday(&end, NULL);  // Lấy mốc thời gian sau khi thực thi lệnh shell
        double execution_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        printf("Execution time: %.6lf seconds\n", execution_time);
    }
    exit(0);
}
