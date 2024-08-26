#include<iostream>
#include<queue>
#include "string.hpp"
/*#include "PATRICIA.hpp"
#include "PATRICIA.cpp"*/

bool GetBit(int BitNumber, int ArraySize, char* Array){
    int TypeSizeInBits = sizeof(char)*8;    
    int ElementNumber = BitNumber / TypeSizeInBits;
    BitNumber = BitNumber % TypeSizeInBits;
    return (bool)((Array[ElementNumber]) & (1u << TypeSizeInBits - 1 - BitNumber));
}

void change(int &b){
    b=228;
    int* a = &b;
    std::cout << *a << std::endl;
}

int main(){
    TString str;
    std::cin >> str;
    if( str == "save"){
        std::cout << "hui";
    }
}