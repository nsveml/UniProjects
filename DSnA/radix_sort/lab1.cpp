#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

const int VALUE_LENGTH = 65;
const int NUMBER_OF_LETTER = 26;
const int NUMBER_OF_INT_KEY = 1000;


struct TKVPair{
    char Key1;
    short Key2;
    char Key3[3];
    char Value [VALUE_LENGTH];
    
 TKVPair(){
        Key1 = '\0';
        Key2 = 0;
        Key3[0] = '\0';
        Value[0] = '\0';
    }
    
    friend ostream& operator<< (ostream &out, const TKVPair &kv);
    friend istream& operator>> (istream &in, TKVPair &kv);
};
 
ostream& operator<< (ostream &out, const TKVPair &kv)
{
    out << kv.Key1 << ' ' << setfill('0') << setw(3) << kv.Key2 << ' ' << kv.Key3 << ' ' << kv.Value;
    return out;
}

istream& operator>> (istream &in, TKVPair &kv)
{
    in >> kv.Key1;
    in >> kv.Key2;
    in >> kv.Key3;
    in >> kv.Value; 
    return in;
}

struct TExpandingArray{
    struct TKVPair * Exar;
    unsigned long long Length;
    int Capacity;
    
    TExpandingArray(){
        Length = 0;
        Capacity = 1;
        Exar = new struct TKVPair[1];
    }
    
    ~TExpandingArray(){
        delete [] Exar;
    }
    
    void InsertElement (struct TKVPair new_elem) {
        if(Capacity == Length){
            struct TKVPair * tmp;
            tmp = new struct TKVPair[Capacity * 2];
            for (int i = 0; i < Length; ++i){
                tmp[i] = Exar[i];
            }
            delete [] Exar;
            Exar = tmp;
            Capacity *= 2;
        }
        Exar[Length] = new_elem;
        Length++;
    }
    
    struct TKVPair & operator [](unsigned long long index){
        if (index >= Length){
            throw out_of_range("Vector outside of range");
        } else {
            return Exar[index];
        }
    }
};

void DigitCountingSort(struct TExpandingArray *dataKeeper, int digitNumber){
    int * counters;
    struct TKVPair * data = new struct TKVPair[dataKeeper->Length];
    int key_to_int;
    if(digitNumber == 1){
        counters = new int[NUMBER_OF_LETTER];
        for(int i = 0; i<NUMBER_OF_LETTER; ++i){
            counters[i] = 0;
        }
        for(int i = 0; i < dataKeeper->Length; ++i){
            counters[(*dataKeeper)[i].Key1-VALUE_LENGTH]++;
        }
        for(int i = 1; i < NUMBER_OF_LETTER; ++i){
            counters[i] += counters[i-1];
        }
        for(int i = dataKeeper->Length-1; i >= 0; --i){
            data[counters[(*dataKeeper)[i].Key1 - VALUE_LENGTH] - 1] = (*dataKeeper)[i];
            counters[(*dataKeeper)[i].Key1 - VALUE_LENGTH]--;
        }
        delete [] counters;
    }
    else if(digitNumber == 2){
        counters = new int [NUMBER_OF_INT_KEY];
        for(int i = 0; i < NUMBER_OF_INT_KEY; ++i){
            counters[i] = 0;
        }
        for(int i = 0; i < dataKeeper->Length; ++i){
            counters[(*dataKeeper)[i].Key2]++;
        }
        for(int i=1; i<NUMBER_OF_INT_KEY; ++i){
            counters[i] += counters[i-1];
        }
        for(int i = dataKeeper->Length-1; i >= 0; --i){ 
            data[counters[(*dataKeeper)[i].Key2] - 1] = (*dataKeeper)[i];
            counters[(*dataKeeper)[i].Key2]--;
        }
        delete [] counters;
    }
    else if(digitNumber == 3){
        counters = new int [NUMBER_OF_LETTER*NUMBER_OF_LETTER];
        for(int i = 0; i < NUMBER_OF_LETTER*NUMBER_OF_LETTER; ++i){
            counters[i] = 0;
        }
        for(int i=0; i<dataKeeper->Length; ++i){
            key_to_int = ((*dataKeeper)[i].Key3[0] - VALUE_LENGTH) * NUMBER_OF_LETTER + ((*dataKeeper)[i].Key3[1] - VALUE_LENGTH);
            counters[key_to_int]++;
        }        
        for(int i = 1; i < NUMBER_OF_LETTER*NUMBER_OF_LETTER; ++i){            
            counters[i] += counters[i-1];
        }       
        for(int i = dataKeeper->Length-1; i >= 0; --i){
            key_to_int = ((*dataKeeper)[i].Key3[0] - VALUE_LENGTH) * NUMBER_OF_LETTER + ((*dataKeeper)[i].Key3[1] - VALUE_LENGTH);          
            data[counters[key_to_int] - 1]=(*dataKeeper)[i];
            counters[key_to_int]--;
        }
        delete [] counters;
    }
    delete [] dataKeeper->Exar;    
    dataKeeper->Exar = data;       
}

void RadixSort(struct TExpandingArray *dataKeeper){
    for(int i = 3; i > 0; --i){
        DigitCountingSort(dataKeeper, i);      
    }
}

int main(){
    
    ios::sync_with_stdio(false);
    
    struct TKVPair temper;
    struct TExpandingArray dataKeeper;
    
    while(cin >> temper){
        dataKeeper.InsertElement(temper);
    }
    RadixSort(&dataKeeper);
    cout<<'\n';
    /*for (int i = 0; i < dataKeeper.Length; ++i){
        cout << dataKeeper[i] << endl;
    }*/
}
