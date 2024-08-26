#include<stdlib.h>
#include<stdio.h>
#include"lib.h"

//compile with -lmylib1 or -lmylib2

int main(){
    int i;
    printf("Enter function number and arguments:\n");
    while(scanf("%d",&i)>0){
        if(i==1){
            while(scanf("%d",&i)>0){
                if(i>0){
                    printf("%f\n", E(i));
                }
                else{
                    break;
                }
            }
        }else if(i==2){
            char* string;
            while(scanf("%d",&i)>0){
                if(i>0){
                    string=Translation(i);
                    printf("%s\n",string);
                    free(string);
                }
                else{
                    break;
                }
            }
        }
    }
}