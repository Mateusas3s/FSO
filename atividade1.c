#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    pid_t r;

    r = fork();

    if(r<0){
        fprintf(stderr, "Fork error!");
        exit(-1);
    }else if(r==0){
        execlp("/bin/ls", "ls", NULL);
    }else{
        wait(NULL);
        printf("Child Complete\n");
        getchar();
    }

    return 0;
}