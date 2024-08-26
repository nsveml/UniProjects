#include<iostream>

int main(){
    unsigned int pattern[1000];
    unsigned int text[1000000];
    int index=0;
    for(int i=0; i<1000; i++){
        std::cin >> pattern[i];
    }
    for(int i=0; i<1000000; i++){
        std::cin >> text[i];
    }
    for(int i=0; i<1000000; i++){
        if(pattern[0] == text[i]){
            while(pattern[index] == text[i+index]){
                if(index < 1000) index++;
                else break;
            }
            if (index==1000) std::cout << i/1000+1 << ", 1" << ", 1\n";
            index = 0;
        }
    }

}