#include "unistd.h"
#include "stdio.h"
#include"stdlib.h"

int touppercase(char *string, int length){
    for(int i=0; i<length; i++){
        if((string[i]>='a')&&(string[i]<='z')) string[i]+='A'-'a';
        if(string[i]=='\n'){string[i]='\0'; return i;}
    }
}

int main(int argc, char*argv[]){
    printf("child1");
    const int MAX_CHAR= 256;
    char string[MAX_CHAR];
    while(read(fileno(stdin),string,MAX_CHAR)>0){
        touppercase(string, MAX_CHAR);
        write(fileno(stdout),string, MAX_CHAR);
        //printf("%s\n",string);
    }
    return 0;
}