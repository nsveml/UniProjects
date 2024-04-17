#include<iostream>

#ifndef figure_h
#define figure_h

class Figure{
    public:
    
    Figure();
    Figure(int a);
    virtual ~Figure();
    virtual size_t VertexesNumber();
    virtual float Area();
    virtual void Print(std::ostream& os);

    protected:

    size_t n;
    float* coords;
    const char* name = "Figure";

};

#include"figure.cpp"

#endif