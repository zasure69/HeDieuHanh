#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define BUFFER_SIZE 10

typedef struct {
    int data[BUFFER_SIZE];
    int count;
} SharedBuffer;

void producer(SharedBuffer* buffer) {
    srand(getpid());  // Khởi tạo seed cho hàm rand() dựa trên pid
    int sum = 0;

    while (sum <= 100) {
        int num = rand() % 11 + 10;  // Tạo số ngẫu nhiên trong khoảng [10, 20]
        while (buffer->count == BUFFER_SIZE) {
            // Nếu buffer đầy, đợi consumer đọc dữ liệu
            usleep(1000);
        }

        buffer->data[buffer->count] = num;
        buffer->count++;
        sum += num;

        printf("Produced: %d\n", num);
        usleep(1000);
    }

    buffer->data[buffer->count] = -1;  // Ghi giá trị -1 vào buffer để thông báo kết thúc
    buffer->count++;
}

void consumer(SharedBuffer* buffer) {
    int sum = 0;

    while (sum <= 100) {
        while (buffer->count == 0) {
            // Nếu buffer trống, đợi producer ghi dữ liệu
            usleep(1000);
        }

        int num = buffer->data[buffer->count - 1];
        buffer->count--;
        sum += num;

        printf("Consumed: %d\n", sum);
        usleep(1000);
    }
}

int main() {
    key_t key = ftok(".", 'A');  // Tạo key cho shared memory
    int shmid = shmget(key, sizeof(SharedBuffer), IPC_CREAT | 0666);  // Tạo segment shared memory
    SharedBuffer* buffer = (SharedBuffer*)shmat(shmid, NULL, 0);  // Gắn segment vào vùng nhớ của tiến trình

    buffer->count = 0;  // Khởi tạo giá trị count của buffer

    pid_t pid = fork();  // Tạo tiến trình con

    if (pid < 0) {
        fprintf(stderr, "Fork failed.\n");
        return 1;
    } else if (pid == 0) {
        // Tiến trình con đóng vai trò là Consumer
        consumer(buffer);
    } else {
        // Tiến trình cha đóng vai trò là Producer
        producer(buffer);

        // Đợi tiến trình con kết thúc
        wait(NULL);

        // Gỡ bỏ segment shared memory
        shmdt(buffer);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}