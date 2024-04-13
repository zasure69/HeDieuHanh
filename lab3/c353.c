#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
int loop_forever = 1;
void on_sigint(){
    printf("\ncount.sh has stopped\n");
    loop_forever = 0;
}

int main(int argc, char* argv[]){
    printf("Welcome to IT007 I am 22520410!\n");
    system("./count.sh 120");
    signal(SIGINT, on_sigint);
    loop_forever = 1;
    while(loop_forever) {}
    exit(0);
}
