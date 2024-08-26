#include<stdio.h>

int main(){
    int i;
    printf("Enter function number and arguments,\
reading of arguments will be stopped when you will enter something which willn't be integer");
    scanf("%d",&i);
    if(i==1){
        while(scanf("%d",&i)){
            printf("%f\n", E(i));
        }
    }else if(i==2){
        char* string;
        while(scanf("%d",&i)){
            string=translate(i);
            printf("%s\n",string);
            free(string);
        }
    }
}