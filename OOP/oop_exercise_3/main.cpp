#include<iostream>
#include<vector>
#include"rectangle.h"
#include"triangle.h"
#include"square.h"

int main(){
    std::cout<<"\
    t - create triangle\n\
    s - create square\n\
    r - create rectangle\n\
    p - print information\n\
    q - quit\n";

    std::vector<Figure*> figures;
    Figure* figure = nullptr;
    char a;

    while(true){
        std::cout << "Enter commands:\n";
        std::cin>>a;
        switch(a){
            case 't':
                std::cout << "Enter coordinates in clockwise order:\n";
                figure = new Triangle(std::cin);
                figures.push_back(figure);
                break;
            case 's':
                std::cout << "Enter coordinatesin clockwise order:\n";
                figure = new Square(std::cin);
                figures.push_back(figure);
                break;
            case 'r':
                std::cout << "Enter coordinates in clockwise order:\n";
                figure = new Rectangle(std::cin);
                figures.push_back(figure);
                break;
            case 'p':
                for(long unsigned int i = 0; i<figures.size(); i++){
                    std::cout << "Number of vertexes:" << figures[i]->VertexesNumber() << "\n";
                    std::cout << "Coordinates:";
                    figures[i]->Print(std::cout);
                    std::cout << "Area:" << figures[i]->Area() << "\n\n\n";
                }
                break;
            case 'q':
                for(long unsigned int i = 0; i < figures.size(); i++){
                    delete figures[i];
                }
                return 0;
                break;
        }
    }
    
}