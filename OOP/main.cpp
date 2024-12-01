#include<iostream>
#include"triangle.h"
#include"rectangle.h"
#include"square.h"
#include"queue.h"

int main(){
    std::cout<<"\
    u - push\n\
    o - pop\n\
    t - top\n\
    c - clear\n\
    i - print\n\
    q - quit\n";

    Triangle triangle;
    TQueue<Triangle> triangles;
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
            case 'c':
                triangles.Clear();
                std::cout << "Cleared\n";
                break;
            case 'i':
                for(auto i : triangles) {
                    std::cout << i << std::endl;
                }
                break;
            case 'q':
                break;
        }
    }
}