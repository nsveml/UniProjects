#include<iostream>
#include"triangle.h"
#include"queue.h"

int main(){
    std::cout<<"\
    u - push\n\
    o - pop\n\
    t - top\n\
    i - print\n\
    c - clear\n\
    q - quit\n";

    Triangle triangle;
    TQueue triangles;
    char a=' ';

    while(a!='q'){
        std::cout << "Enter commands:\n";
        std::cin>>a;
        switch(a){
            case 'u':
                std::cout << "Enter coordinates in clockwise order:\n";
                std::cin >> triangle;
                triangles.Push(triangle);
                break;
            case 'o':
                std::cout << triangles.Pop();
                break;
            case 't':
                std::cout << triangles.Top();
                break;
            case 'i':
                std::cout << triangles;
                break;
            case 'c':
                triangles.Clear();
                std::cout << triangles;
            case 'q':
                break;
        }
    }
}