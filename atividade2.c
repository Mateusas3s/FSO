#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int r, pid, s;

    r = fork();

    if(r<0){
        fprintf(stderr, "Fork error!");
        exit(-1);
    }else if(r==0){ //processo filho
        printf("sou filho com PID: %d, meu pai tem PID: %d\n", getpid(), getppid());
    }else{ // processo pai
        printf("sou o pai com o PIP: %d, criei um filho com PID: %d\n", getpid(), r);

        pid = wait(&s);

        printf("meu filho com pid %d terminou com o status %d\n", pid, s);
        getchar();
        exit(0);
    }

    return 0;
}