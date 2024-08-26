//lib2

#include"lib.h"
#include<stdlib.h>

// -fPIC -shared

float E(int x){
    unsigned long long fact=1;
    float e=1.0;
    for(int i=1; i<=x; i++){
        e+=1.0/(float)fact;
        fact*=fact+1;
    }
    return e;
}

char* Translation(long x){
    int length=0, capacity=1, base = 3, diff = '0';
    char* translation = (char*)malloc(2*sizeof(char));
    translation[1] = '\0';
    while(x>=base){
        if(capacity==length){
            capacity*=2;
            translation=(char*)realloc(translation, (capacity+1)*sizeof(char));
        }
        translation[length]=x%base+'0';
        x/=base;
        length++;
    }
    if(capacity==length){
        translation=(char*)realloc(translation,(length+2)*sizeof(char));
    }
    translation[length]=x+'0';
    translation[length+1]='\0';
    length++;
    char tmp;
    for(int i=0; i<length/2; i++){
        tmp=translation[i];
        translation[i]=translation[length-i-1];
        translation[length-i-1]=tmp;
    }
    return translation;
}
