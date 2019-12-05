#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int _len;

int main(){

    pid_t r, s, t, u, v, w;
    char str[101];
    char nulo[1] = {"_"};
    char vogais[11] = {"aeiouAEIOU\0"};
    int j, k;

    printf("Insira uma String: ");
    scanf("%s", str);

    r = fork();

    if(r<0){
        fprintf(stderr, "Fork error!\n");
        exit(-1);
    }
    else if(r==0){
        s = fork();
        if(s<0){
            fprintf(stderr, "Fork error!\n");
            exit(-1);
        }
        else if(s==0){
            
            _len = strlen(str)-1;
            printf("O processo %d retorna o tamanho da String: %d\n", getpid(), _len);
            exit(_len);

        }else{
            wait(&_len);
            _len = WEXITSTATUS(_len);
            exit(_len);
        }
    }else{
        wait(&_len);
        printf("O processo %d imprime o tamanho da String: %d\n", getpid(), WEXITSTATUS(_len));

        t = fork();
        if(t<0){
            fprintf(stderr, "Fork error!\n");
            exit(-1);
        }
        else if(t==0){
            u = fork();

            if(u<0){
                fprintf(stderr, "Fork error!\n");
                exit(-1);
            }
            else if(u==0){

                for(j = 0; j<strlen(str); j++){
                    if(isupper(str[j])!=0){
                        str[j] = nulo[0];
                    }
                }
                printf("O processo %d imprime a String sem os caracteres maiúsculos: %s\n", getpid(), str);
                pause();


            }else{
                v = fork();

                if(v<0){
                    fprintf(stderr, "Fork error!\n");
                    exit(-1);
                }
                else if(v==0){
                    for(j = 0; j<strlen(str); j++){
                        if(islower(str[j])!=0){
                            str[j] = nulo[0];
                        }
                    }

                    printf("O processo %d imprime a String sem os caracteres minúsculos: %s\n", getpid(), str);
                    pause();


                }else{
                    w = fork();

                    if(w<0){
                        fprintf(stderr, "Fork error!\n");
                        exit(-1);
                    }
                    else if(w==0){
                    
                        for(j = 0; j<(int)strlen(str); j++){
                            for(k = 0; k<(int)strlen(vogais); k++){
                                if(str[j] == vogais[k]){
                                    str[j] = nulo[0];
                                }
                            }
                        }

                        printf("O processo %d imprime a String sem as vogais: %s\n", getpid(), str);
                        pause();

                    }else{
                        pause();
                    }
                }
            }

        }else{
            pause();
        }
        pause();
    }

    return 0;
}