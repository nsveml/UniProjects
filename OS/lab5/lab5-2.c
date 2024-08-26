#include<stdio.h>
#include<stdlib.h>
#include<dlfcn.h>
#include"lib.h"

//compile with -ldl

int main(int argc, char*argv[]){
    char* firstlib=argv[1], *secondlib=argv[2];

    void* lib1 = dlopen(firstlib, RTLD_LAZY);
    void* lib2 = dlopen(secondlib, RTLD_LAZY);
    
    int i=0, j=0;
    if(lib1 == NULL){
        perror("dlopen1");
    }
    if(lib2 == NULL){
        perror("dlopen2");
    }

    float (*func1) (int);
    char* (*func2) (long);
    func1=dlsym(lib1, "E");
    func2=dlsym(lib1, "Translation");
    if(func1==NULL) perror("func1 error");
    if(func2==NULL) perror("func2 error");

    while(scanf("%d",&i)>0){
        if(i==0){
            if(j==0){
                printf("%s switched to %s\n", firstlib, secondlib);
                func1=dlsym(lib2, "E");
                func2=dlsym(lib2, "Translation");
                if(func1==NULL) perror("func1 error");
                if(func2==NULL) perror("func2 error");
                j++;
            }
            else{
                printf("%s switched to %s\n", secondlib, firstlib);
                func1=dlsym(lib1, "E");
                func2=dlsym(lib1, "Translation");
                if(func1==NULL) perror("func1 error");
                if(func2==NULL) perror("func2 error");
                j--;
            }
        }
        else if(i==1){
            scanf("%d", &i);
            printf("%f\n", func1(i));
        }else if(i==2){
            char* string;
            scanf("%d",&i);
            string=func2(i);
            printf("%s\n",string);
            free(string);
        }
    }
    dlclose(lib1);
    dlclose(lib2);
}