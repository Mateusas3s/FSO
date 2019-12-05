#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int main(){

    int i, j, k, r, pos, pid_first, ppid_first, branch_3sons;
    int op = 0;
    int isBranch = TRUE;
    int isValid0 = TRUE;
    char str[101];
    char nulo[1] = {"_"};
    char vogais[11] = {"aeiouAEIOU\0"};

    ppid_first = getppid();
    pid_first = getpid();
    fgets (str, 101, stdin);
    printf("A string digitada é: %s\n", str);

    for(i=0; i<3; i++){
        if(i<2){
            r = fork();
            if(isBranch==TRUE){
                branch_3sons = getpid();
                isBranch = FALSE;
            }
            if(i==1 && getppid()!=pid_first && getppid()!=ppid_first){
                printf("O processo [%d] mostra o tamanho da String: %d\n", getpid(), (int)strlen(str)-1);
            }

        }else{
            if(getppid()==pid_first){
                r = fork();
                if(r==0 && getppid()==branch_3sons){
                    for(j = 0; j<(int)strlen(str); j++){
                        if(islower(str[j])!=0){
                            str[j] = nulo[0];
                        }
                    }
                    printf("O processo [%d] retira os caracteres minusculos: %s\n", getpid(), str);
                    getchar();
                }

                if(r==0 && getppid()!=branch_3sons){
                    for(j = 0; j<(int)strlen(str); j++){
                        if(isupper(str[j])!=0){
                            str[j] = nulo[0];
                        }
                    }
                    printf("O processo [%d] retira os caracteres maiusculos: %s\n", getpid(), str);
                }

                if(getpid()==branch_3sons){              
                    r = fork();
                    if(r==0){
                        for(j = 0; j<(int)strlen(str); j++){
                            for(k = 0; k<(int)strlen(vogais); k++){
                                if(str[j] == vogais[k]){
                                    str[j] = nulo[0];
                                }
                            }
                        }
                        printf("O processo [%d] retira as vogais: %s\n", getpid(), str);
                    }
                }
            }
        }
            
        if(r<0){
            fprintf(stderr, "Erro ao fazer o Fork!");
            exit(-1);
        }
        getchar();
        
    }
    return 0;
}