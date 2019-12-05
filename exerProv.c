#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

int main(){

    pid_t r, s, t, u;

    r = fork();

    if(r<0){
        fprintf(stderr, "Fork error!");
        exit(-1);
    }
    else if(r==0){
        pause();
    }else{
        s = fork();
        
        if(s<0){
            fprintf(stderr, "Fork error!");
            exit(-1);
        }else if(s==0){
            fork();
        }else{
            t = fork();

            if(t<0){
                fprintf(stderr, "Fork error!");
                exit(-1);
            }else if(t==0){
                u = fork();

                if(u<0){
                    fprintf(stderr, "Fork error!");
                    exit(-1);
                }else if(u==0){
                    pause();
                }else{
                    fork();
                }
            }else{
                pause();
            }
        }

        pause();
    }

    return 0;
}