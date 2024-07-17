#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"figure.h"

class Triangle : public Figure{
    public:
    
    Triangle();

    Triangle(std::istream& is) : Figure(3, is){}

    Triangle& operator=(const Triangle& other);
    bool operator==(const Triangle& other);

};

#include"triangle.cpp"

#endif