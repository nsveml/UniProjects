#include<iostream>

#ifndef figure_h
#define figure_h

class Figure{
    public:
    
    Figure();
    Figure(int a, std::istream& is);
    Figure(const Figure& other);
    Figure& operator=(const Figure& other);
    bool operator==(const Figure& other);
    virtual ~Figure();
    virtual size_t VertexesNumber();
    virtual float Area() const;
    virtual void Print(std::ostream& os);



    friend std::ostream& operator<<(std::ostream& os, const Figure& figure);
    friend std::istream& operator>>(std::istream& is, const Figure& figure);

    protected:

    const char* name = "Figure";
    size_t n;
    float* coords;

};

#include"figure.cpp"

#endif