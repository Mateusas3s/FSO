#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void printRand(){
    srand(time(NULL));
    int x = rand()%200;
    printf("-> %d\n", x);
    exit(x);
}

int main(){

    printRand();

    if(fork()){
        int y;
        wait(&y);
        printf("recebi %d\n", WEXITSTATUS(y));
    }
    while(1){

        pause();
    }
    return 0;
}