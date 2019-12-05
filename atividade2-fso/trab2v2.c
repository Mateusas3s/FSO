#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h> 

int m_input1[2000][2000];
int m_input2[2000][2000];
int m_output[2000][2000];

int len;

pid_t pid1, pid2;

void print1(){
    int i, j;
    //printf("%d\n", getpid());
    for(i=0;i<len/2;i++){
        for(j=0;j<len;j++){
            printf("%d ", m_output[i][j]);
        }
        printf("\n");
    }
    exit(1);
}

void print2(){
    int i, j;    
    //printf("%d\n", getpid());
    for(i=len/2;i<len;i++){
        for(j=0;j<len;j++){
            printf("%d ", m_output[i][j]);
        }
        printf("\n");
    }

    exit(0);
}

void printOk1(){
    //printf("%d\n", getpid());
    kill(pid1, SIGUSR1);
}

void printOk2(){
    //printf("%d\n", getpid());
    //wait(NULL);
    kill(pid2, SIGUSR2);
}

int main(){

    //signal(SIGUSR1, printOk1);
    //signal(SIGUSR2, printOk2);

    int i, j, k, val, status;

    pid_t pid_fin1 = WIFSTOPPED(status);
    pid_t pid_fin2 = WIFSTOPPED(status);

    if(pid_fin1 == pid1 && pid_fin2 == pid2){
        printOk1();
        printOk2();
    }

    scanf("%d", &len);

    //printf("%d\n", getpid());
    for(i=0;i<len;i++){
        for(j=0;j<len;j++){
            scanf("%d", &val);
            m_input1[i][j] = val;
        }
    }

    for(i=0;i<len;i++){
        for(j=0;j<len;j++){
            scanf("%d", &val);
            m_input2[i][j] = val;
        }
    }
    printf("\n");

    pid1 = fork();

    if(pid1<0){
        fprintf(stderr, "Fork error!\n");
        exit(-1);
    }
    else if(pid1==0){//filho
        signal(SIGUSR1, print1);

        for(i=0;i<len/2;i++){
            for(j=0;j<len;j++){
                m_output[i][j] = 0;
                for(k=0;k<len;k++){
                    m_output[i][j]+=m_input1[i][k]*m_input2[k][j];
                }
            }
        }
        //kill(getppid(), SIGUSR1);
        pause();
        
    }else{//pai
        pid2 = fork();

        if(pid2<0){
            fprintf(stderr, "Fork error!\n");
            exit(-1);
        }
        else if(pid2==0){//filho
            signal(SIGUSR2, print2);

            for(i=len/2;i<len;i++){
                for(j=0;j<len;j++){
                    m_output[i][j] = 0;
                    for(k=0;k<len;k++){
                        m_output[i][j]+=m_input1[i][k]*m_input2[k][j];
                    }
                }
            }
            //kill(getppid(), SIGUSR2);
            pause();

        }else{//pai


            pause();

        }
    }

    return 0;
}