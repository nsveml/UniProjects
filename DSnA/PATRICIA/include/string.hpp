#pragma once
#include <iostream>

class TString{
    public:
    using ValueType = char;
    
    
    TString();
    TString(int);
    TString(const TString &);
    TString(ValueType* &&, int);

    TString(const ValueType*, int);
    void PushBack(ValueType);
    
    ValueType* cstr();

    void clear();

    ~TString();

    int Size();
    
    ValueType& operator [](int);

    bool operator == (const TString&) const;

    bool operator == (const ValueType *) const;
    
    TString& operator = (const TString&);
    TString& operator = (ValueType* &&);

    TString& operator = (const ValueType*);
    void ToLower();
    friend std::ostream& operator<< (std::ostream &, const TString &);
    friend std::istream& operator>> (std::istream &, TString &);

    private:
    ValueType* str;
    int length;
    int capacity;

    void Reallocate(int);
    
    void Updatelength();
    
};


std::ostream& operator<< (std::ostream &, const TString &);

std::istream& operator >> (std::istream&, TString&);

bool StringsEqual (const char*, const char*);