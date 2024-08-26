#include "unistd.h"
#include "stdio.h"
#include"stdlib.h"

void doublespaces(char *string, int length){
    char *str;
    str=malloc(sizeof(char)*length);
    int j=1;
    str[0]=string[0];
    for(int i=1; i<length;i++){
        if((str[j-1]!=' ')&&(string[i]==' ')){
            str[j]=string[i];
            j++;
        }
        else if(string[i]!=' '){
            str[j]=string[i];
            j++;
        }
        else if(string[i]=='\n'){
            str[j]='\0';
            break;
        }
    }
    for(int i=0; i<=j; i++){
        string[i]=str[i];
    }
    free(str);
}

int main(int argc, char*argv[]){
    const int MAX_CHAR = 256;
    printf("child2");
    char string[MAX_CHAR];
    while(read(fileno(stdin),string,MAX_CHAR)>0){
        doublespaces(string, MAX_CHAR);
        write(fileno(stdout),string, MAX_CHAR);
        //printf("%s\n",string);
    }
    return 0;
}