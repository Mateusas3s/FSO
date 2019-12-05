#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void beep(){
    printf("BEEP\n");
}

int main(){
    printf("%d\n", getpid());

    signal(SIGUSR1, beep);

    while(1){

        pause();
    }
    return 0;
}