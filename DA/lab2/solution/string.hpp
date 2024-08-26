#ifndef STR_HPP
#define STR_HPP

#include <iostream>
#pragma once

class TString{
    public:
    using ValueType = char;
    
    
    TString(){
        capacity = 1;
        length = 0;
        str = new ValueType[1];
        str[0]= '\0';
    }
    TString(int arg_capacity) {
        str = new ValueType[arg_capacity + 1];
        length = 0;
        capacity = arg_capacity;
    }
    TString(const TString &other){
        capacity = other.capacity;
        length = other.length;
        str = new char[capacity + 1];
        for(int i=0; i<length; i++){
            str[i]=other.str[i];
        }
        str[length]='\0';
    }
    TString(ValueType* &&other, int Size) {
        str = other;
        length = Size;
        capacity = Size;
        other = nullptr;
    }

    TString(const ValueType* other, int Size) {
        Reallocate(Size);
        length = 0;
        while (length < Size) {
            str[length++] = *other++;
        }
        str[length] = 0;
        capacity = length;
    }
    void PushBack(ValueType new_elem){
        if(capacity==length+1){
            ValueType* tmp;
            tmp = new ValueType[capacity * 2];
            for (int i=0; i<length; ++i){
                tmp[i]=str[i];
            }
            tmp[length]='\0';
            delete [] str;
            str = tmp;
            capacity*=2;
        }
        str[length]=new_elem;
        length++;
        str[length]='\0';
    }
    
    ValueType* cstr(){
        return str;
    } 

    void clear(){
        if(str != nullptr) delete [] str;
        str = nullptr;
        capacity = 0;
        length = 0;
    }

    ~TString(){
        clear();
    }

    int Size(){
        return length;
    }
    
    ValueType& operator [](int index) {
        if (index >= length){
            throw std::out_of_range("String outside of range");
        } else {
            return str[index];
        }
    }

    bool operator == (const TString& str2) const {
       if((str == nullptr)||(str2.str==nullptr)){
           return str == str2.str;
       }
       else if(length == str2.length){
           int i = 0;
           while(i < length){
                if (str[i] != str2.str[i]) {
                    return false;
                }
                ++i;
            }
            return true;
        }
        else return false;
    }

    bool operator == (const ValueType * str2) const {
        int i=0;
        if(str==nullptr){
            return false;
        }
        else{
            while(str[i]==str2[i] && i < length){
                //printf("%c -- %c\n", str[i], str2[i]);
                if((str[i]!='\0')&&(str2[i]=='\0')){
                    return false;
                }
                i++;
            }
            if(str[i] == str2[i]) return true;
            else return false;
        }
    }
    
    TString& operator = (const TString& other) {
        if (str != nullptr) {
            delete[] str;
        }
        str = new ValueType[other.length+1];
        length = other.length;
        capacity = length;
        for (int i = 0; i < other.length; ++i) {
            str[i] = other.str[i];
        }
        str[length]='\0';
        return *this;
    }
    TString& operator = (ValueType* &&other) {
        
        if (str != nullptr) {
            delete[] str;
        }
        str = other;
        other = nullptr;
        length = 0;
        while (str[length++] != 0);
        capacity = --length;
        return *this;
    }

    TString& operator = (const ValueType* other) {
        static const int BUFF_length = 256;
        if (str != nullptr) {
            if (capacity < BUFF_length) {
                Reallocate(BUFF_length);
            }
        }
        length = 0;
        while (*other != 0 && length < capacity) {
            str[length++] = *other++;
        }
        str[length] = 0;

        return *this;
    }
    void ToLower(){
        if(str == nullptr) {
            return;
        }
        int diff='a'-'A';
        for(int i=0; i<length; i++){
            if((str[i]<='Z')&&(str[i]>='A')){
                str[i]+=diff;
            }
        }
    }
    friend std::ostream& operator<< (std::ostream &out, const TString &str);
    friend std::istream& operator>> (std::istream &in, TString &str);

    private:
    ValueType* str;
    int length;
    int capacity;

    void Reallocate(int NewCapacity){
        ValueType *tmp = new ValueType[NewCapacity + 1];
        for (int i = 0; i < length; ++i) {
            tmp[i]=str[i];
        }
        tmp[length]='\0';
        delete [] str;
        str = tmp;
        capacity = NewCapacity;
    }
    
    void Updatelength(){
        length = 0;
        if (str == nullptr) {
            return;
        }
        while (str[length] != '\0') {
            ++length;
        }
        return;
    }
    
};


std::ostream& operator<< (std::ostream &out, const TString &str) {
    out << str.str;
    return out;
}

std::istream& operator >> (std::istream& in, TString& str) {
    static const int BUFF_length = 256;
    if (str.capacity < BUFF_length) {
        str.Reallocate(BUFF_length);
    }
    if(in >> str.str){
        str.Updatelength();
    }
    return in;
}

bool StringsEqual (const char* a, const char* b){
    int i = 0;
    while(a[i] != 0 && b[i] != 0){
        if (a[i] != b[i]) {
            return false;
        }
        i++;
    }
    return a[i] == b[i];
}

#endif