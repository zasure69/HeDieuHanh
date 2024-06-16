
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <termios.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_LINE 80 /* The maximum length command */
#define HISTORY_SIZE 10 /* Maximum number of commands to store in history */

void handle_sigint(int sig) {
}

void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void disableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO); // Enable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void parseArgument (char input[], char *args[], char **input_file, char **output_file) {
    // Parse input into arguments and check for redirection
    int i = 0;
    char *token = strtok(input, " ");
    *input_file = NULL;
    *output_file = NULL;

    while (token != NULL) {
        if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                *output_file = token;
            }
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " ");
            if (token != NULL) {
                *input_file = token;
            }
        } else {
            args[i++] = token;
        }
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

void executeCommand(char *args[], char *input_file, char *output_file) {
    // Handle input redirection
    if (input_file != NULL) {
        int fd = open(input_file, O_RDONLY);
        if (fd == -1) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd, STDIN_FILENO) == -1) {
            perror("dup2 failed");
            exit(1);
        }
        close(fd);
    }

    // Handle output redirection
    if (output_file != NULL) {
        int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1) {
            perror("open failed");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            exit(1);
        }
        close(fd);
    }

    if (execvp(args[0], args) == -1) {
        perror("execvp failed");
        exit(1);
    }
}

int main(void) {
    char *args[MAX_LINE / 2 + 1]; /* command line arguments */
    int should_run = 1; /* flag to determine when to exit program */
    char history[HISTORY_SIZE][MAX_LINE]; /* History buffer */
    int history_count = 0; /* Number of commands in history */
    int history_index = 0; /* Current history index for navigation */
    // Set up SIGINT signal handler
    signal(SIGINT, handle_sigint);
    while (should_run) {
        char input[MAX_LINE] = {0};
        int input_index = 0;
        int in_history_mode = 0;

        printf("it007sh> ");
        fflush(stdout);

        enableRawMode();

        while (1) {
            char c = getchar();

            if (c == '\n') {
                if (input_index > 0) {
                    input[input_index] = '\0';
                    strncpy(history[history_count % HISTORY_SIZE], input, MAX_LINE);
                    history_count++;
                }
                break;
            } else if (c == 127) { // Handle backspace
                if (input_index > 0) {
                    input_index--;
                    printf("\b \b");// Move cursor back, print space (to overwrite character), move cursor back again
                    fflush(stdout);
                }
            } else if (c == 27) { // Handle arrow keys (arrow keys input push buffer esc key ([^), [, and arrow key)
                getchar(); // Skip the [
                switch (getchar()) {
                    case 'A': // Up arrow
                        if (history_count > 0) {
                            if (!in_history_mode) {
                                history_index = (history_count - 1) % HISTORY_SIZE;
                                in_history_mode = 1;
                            } else if (history_index > 0) {
                                history_index--;
                            }
                            strcpy(input, history[history_index % HISTORY_SIZE]);
                            input_index = strlen(input);
                            printf("\r\033[K"); // \r -> move cursor to the beginning of current line, \r\033[K -> Clears the line from the cursor position to the end of the line
                            printf("it007sh> %s", input);
                            fflush(stdout);
                        }
                        break;
                    case 'B': // Down arrow
                        if (in_history_mode) {
                            if (history_index < (history_count - 1)) {
                                history_index++;
                                strcpy(input, history[history_index % HISTORY_SIZE]);
                                input_index = strlen(input);
                                printf("\r\033[K");
                                printf("it007sh> %s", input);
                                fflush(stdout);
                            } else {
                                input[0] = '\0';
                                input_index = 0;
                                in_history_mode = 0;
                                printf("\r\033[K");
                                printf("it007sh> ");
                                fflush(stdout);
                            }
                        }
                        break;
                }
            } else {
                input[input_index++] = c;
                putchar(c);
                fflush(stdout);
            }
        }

        disableRawMode();
        printf("\n");

        char *pipe_p = strchr(input, '|');

        if (pipe_p != NULL) {
            *pipe_p = '\0'; //replace '|' by NULL
            char *first_command = input;
            char *second_command = pipe_p + 1;

            char *args1[MAX_LINE / 2 + 1];
            char *args2[MAX_LINE / 2 + 1];
            char *input_file1 = NULL;
            char *output_file1 = NULL;
            char *input_file2 = NULL;
            char *output_file2 = NULL;

            parseArgument(first_command, args1, &input_file1, &output_file1);
            parseArgument(second_command, args2, &input_file2, &output_file2);

            int fd[2];
            if (pipe(fd) == -1) {
                perror("pipe failed");
                exit(1);
            }

            pid_t pid1 = fork();
            if (pid1 < 0) {
                perror("fork failed");
                exit(1);
            } else if (pid1 == 0) {
                /* Child process */
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                close(fd[1]);
                executeCommand(args1, input_file1, output_file1);
            }

            pid_t pid2 = fork();
            if (pid2 < 0) {
                perror("fork failed");
                exit(1);
            } else if (pid2 == 0) {
                /* Child process */
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                executeCommand(args2, input_file2, output_file2);
            }

            close(fd[0]);
            close(fd[1]);

            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);

        } else {
            char *input_file = NULL;
            char *output_file = NULL;
            parseArgument(input, args, &input_file, &output_file);

            /* Check if the command is "exit" */
            if (args[0] != NULL && strcmp(args[0], "exit") == 0) {
                should_run = 0;
                continue;
            }

            /* Fork a child process to execute the command */
            pid_t pid = fork();
            if (pid < 0) {
                perror("fork failed");
                exit(1);
            } else if (pid == 0) {
                /* Child process */
                executeCommand(args, input_file, output_file);
                exit(1);
            } else {
                /* Parent process */
                wait(NULL); /* Wait for the child process to complete */
            }
        }       
    }

    return 0;
}
