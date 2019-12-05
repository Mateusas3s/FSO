#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h> 

int m_input1[2000][2000];
int m_input2[2000][2000];
int m_output[2000][2000];

int len, ok1 = 0, ok2 = 0;

pid_t pid1, pid2;

void print1(){
    int i, j;
    //printf("%d\n", getpid());
    for(i=0;i<len/2;i++){
        for(j=0;j<len;j++){
            if(j==len-1){
                printf("%d", m_output[i][j]);
            }else{
                printf("%d ", m_output[i][j]);
            }
        }
        printf("\n");
    }
    exit(0);
}

void print2(){
    int i, j;    
    //printf("%d\n", getpid());
    for(i=len/2;i<len;i++){
        for(j=0;j<len;j++){
            if(j==len-1){
                printf("%d", m_output[i][j]);
            }else{
                printf("%d ", m_output[i][j]);
            }
        }
        printf("\n");
    }
    exit(0);
}

void printOk(){

    if(ok1==1 && ok2==1){
        kill(pid1, SIGINT);
        wait(NULL);
        kill(pid2, SIGCONT);
        wait(NULL);
        exit(0);
    }
}

void printOk1(){
    ok1++;
    printOk();
}

void printOk2(){
    ok2++;
    printOk();
}

void nada(){

}

int main(){

    signal(SIGUSR1, printOk1);
    signal(SIGUSR2, printOk2);

    int i, j, k;

    scanf("%d", &len);

    //printf("%d\n", getpid());
    for(i=0;i<len;i++){
        for(j=0;j<len;j++){
            scanf("%d", &m_input1[i][j]);
        }
    }

    for(i=0;i<len;i++){
        for(j=0;j<len;j++){
            scanf("%d", &m_input2[i][j]);
        }
    }
    //printf("\n");

    pid1 = fork();

    if(pid1<0){
        fprintf(stderr, "Fork error!\n");
        exit(-1);
    }
    else if(pid1==0){//filho
        signal(SIGINT, nada);

        for(i=0;i<len/2;i++){
            for(j=0;j<len;j++){
                m_output[i][j] = 0;
                for(k=0;k<len;k++){
                    m_output[i][j]+=m_input1[i][k]*m_input2[k][j];
                }
            }
        }

        kill(getppid(), SIGUSR1);
        pause();
        print1();
        
    }else{//pai
        pid2 = fork();

        if(pid2<0){
            fprintf(stderr, "Fork error!\n");
            exit(-1);
        }
        else if(pid2==0){//filho
            signal(SIGCONT, nada);

            for(i=len/2;i<len;i++){
                for(j=0;j<len;j++){
                    m_output[i][j] = 0;
                    for(k=0;k<len;k++){
                        m_output[i][j]+=m_input1[i][k]*m_input2[k][j];
                    }
                }
            }
            kill(getppid(), SIGUSR2);
            pause();
            print2();

        }else{//pai

            wait(NULL);

        }
    }

    return 0;
}