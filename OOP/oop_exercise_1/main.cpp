#include <iostream>

class FuzzyNumber{
    public:
    
    float el, x, er;
    
    FuzzyNumber(){
        x=0.0;
        el=0.0;
        er=0.0;
    }

    FuzzyNumber(float a, float b, float c){
        el=a;
        x=b;
        er=c;
    }
    
    FuzzyNumber oposite(){
        FuzzyNumber tmp;
        tmp.x=1.0/x;
        tmp.el=1/er;
        tmp.er=1/el;
        return tmp;
    }
};

FuzzyNumber operator+(FuzzyNumber a, FuzzyNumber b){
    FuzzyNumber c;
    c.el=a.el+b.el;
    c.er=a.er+b.er;
    c.x=a.x+b.x;
    return c;
}

FuzzyNumber operator-(FuzzyNumber a, FuzzyNumber b){
    FuzzyNumber c;
    c.el=a.el-b.el;
    c.er=a.er-b.er;
    c.x=a.x-b.x;
    return c;
}

FuzzyNumber operator*(FuzzyNumber a, FuzzyNumber b){
    FuzzyNumber c;
    c.x=a.x*b.x;
    c.el=a.el*b.el;
    c.er=a.er*b.er;
    return c;
}

FuzzyNumber operator/(FuzzyNumber a, FuzzyNumber b){
     return a*b.oposite();
}

bool operator < (FuzzyNumber a, FuzzyNumber b){
    return (a.x<b.x);
}

bool operator > (FuzzyNumber a, FuzzyNumber b){
    return (a.x>b.x);
}

bool operator ==(FuzzyNumber a, FuzzyNumber b){
    return (a.x==b.x);
}


std::ostream& operator <<(std::ostream& out, const FuzzyNumber &a){
    out<<'('<<a.el<<", "<<a.x<<", "<<a.er<<")";
    return out;
}

std::istream& operator >>(std::istream &in, FuzzyNumber &a){
    char c;
    in>>a.x>>c>>a.er;
    a.el = a.x - a.er;
    a.er = a.x + a.er;
    return in;
}

int main(){
    FuzzyNumber a, b;
    std::cout<<"Enter two fuzzy numbers <x, e>:\n";
    std::cin>>a>>b;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    std::cout<<"a + b="<<a+b<<std::endl;
    std::cout<<"a - b = "<<a-b<<std::endl;
    std::cout<<"a * b = "<<a*b<<std::endl;
    std::cout<<"a / b = "<<a/b<<std::endl;
    std::cout<<"1/a = "<<a.oposite()<<std::endl;
    std::cout<<"a = "<<a<<std::endl;
    std::cout<<"b = "<<b<<std::endl;
    if(a>b) std::cout<<"a bigger then b" << std::endl;
    if(a<b) std::cout<<"a less then b" << std::endl;
    if(a==b) std::cout<<"a equal b" << std::endl;
}
