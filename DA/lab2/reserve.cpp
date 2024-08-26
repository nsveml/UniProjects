#include <iostream>
#include <stdlib.h>

class TString{
    public:
    using ValueType = char;
    
    
    TString(){
        capacity = 1;
        length = 0;
        str = new ValueType[1];
        str[0]= '\0';
    }

    TString(const TString &other){
        capacity = other.capacity;
        length = other.length;
        str = new char[length+1];
        for(int i=0; i<length; i++){
            str[i]=other.str[i];
        }
        str[length]='\0';
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
    }

    ~TString(){
        if(str != nullptr) delete [] str;
        str = nullptr;
    }

    int size(){
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
       if((str==nullptr)||(str2.str==nullptr)){
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

    TString& operator = ( ValueType* other) {
    if (str != nullptr) {
        delete[] str;
    }
    str = other;
    other = nullptr;
    Updatelength();
    return *this;
    }
    
    friend std::ostream& operator<< (std::ostream &out, const TString &str);
    friend std::istream& operator>> (std::istream &in, TString &str);

    private:
    ValueType* str;
    int length;
    int capacity;

    void Reallocate(int NewCapacity){
        int i=0;
        ValueType *tmp;
        tmp = new ValueType[NewCapacity];
        while((str[i]!='\0')&&(i<NewCapacity-1)){
            tmp[i]=str[i];
            i++;
        }
        tmp[i]='\0';
        delete [] str;
        str = tmp;
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
};


std::ostream& operator<< (std::ostream &out, const TString &str) {
    out << str.str;
    return out;
}

std::istream& operator >> (std::istream& in, TString& str) {
    static const int BUFF_length = 256;
    str.Reallocate(BUFF_length+1);
    if(in >> str.str){
        str.Updatelength();
        str.ToLower();
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

class TPatricia {

    public:

        static const char FILE_HEADER [];
        static const int SIZE_OF_HEADER;

        using KeyType = TString;
        using ValueType = unsigned long long;

        TPatricia(){
            Root = nullptr;
        }
        void Clear();
        int AddNode(KeyType &, ValueType);
        
        int DeleteNode(KeyType&);
        
        ValueType* FindNode(KeyType&);
        
        int SaveInFile(KeyType);
        
        int LoadFromFile(KeyType);
        
        ~TPatricia();
    private:

        struct TNode{
            KeyType Key;
            ValueType Value;
            int BitNumber;
            TNode * Left;
            TNode * Right;
            
            TNode(){
                BitNumber=-1;
                Left = nullptr;
                Right = nullptr;
            }
            
            ~TNode(){
                Key.clear();
                Left = nullptr;
                Right = nullptr;
            }

            TNode& operator = (const TNode& second){
                Key = second.Key;
                Value = second.Value;
                BitNumber = second.BitNumber;
                Left = second.Left;
                Right = second.Right;
                return *this;
            }
        };

        TNode *Root;

        void SaveTree(TNode *, FILE *);

        TNode*  LoadTree(TNode *, bool, FILE *);

        void RemoveTree(TNode*);
        
        bool GetBit(int, int,  KeyType&); 

        int FindBitDifference(TNode &, TNode &);
        
        int InsertNode(TNode &, TNode &);
        
        ValueType* NodeSearch(TNode &, KeyType&, int);
        
};

const char TPatricia::FILE_HEADER [] = "MY_PATRICIA";
const int TPatricia::SIZE_OF_HEADER = sizeof(FILE_HEADER) - 1u;

bool TPatricia::GetBit(int BitNumber, int ArraySize, KeyType& Array){
    int TypeSizeInBits = sizeof(KeyType::ValueType)*8;    
    int ElementNumber = BitNumber / TypeSizeInBits;
    if(ElementNumber >= ArraySize || ElementNumber < 0) return 0;
    BitNumber = BitNumber % TypeSizeInBits;
    return (bool)((Array[ElementNumber] >> BitNumber) & 1u);
}

int TPatricia::FindBitDifference(TNode &Receiving, TNode &Incoming){
    int FBD, i = 0;
    while(Incoming.Key[i] == Receiving.Key[i]){
        i++;
        if(i == Incoming.Key.size() || i == Receiving.Key.size()){
            break;
        }
    }
    if(i == Incoming.Key.size() && i == Receiving.Key.size()){
        FBD = -2;
    }
    else if((i <= Incoming.Key.size()) && (i <= Receiving.Key.size())){
        i*=sizeof(char)*8;
        for(int j = 0; j < sizeof(char)*8; j++){
            int a, b;
            a = GetBit(i + j, Receiving.Key.size(), Receiving.Key);
            b = GetBit(i + j, Incoming.Key.size(), Incoming.Key);
            if(a != b){
                FBD = i + j;
                break;
            }
        }
    }
    return FBD;
}

int TPatricia::InsertNode(TNode& Receiving, TNode& Incoming){
    bool IncBit;
    if(Incoming.BitNumber < Receiving.BitNumber){
        Incoming.BitNumber = Receiving.BitNumber;
        if( Receiving.Right == nullptr){
            IncBit = 0;
            InsertNode(*(Receiving.Left), Incoming);
        }
        else if( IncBit = GetBit(Receiving.BitNumber-1, Incoming.Key.size(), Incoming.Key)){
            InsertNode(*(Receiving.Right), Incoming);
        }
        else{
            InsertNode(*(Receiving.Left), Incoming);
        }
    }
    else{
        Incoming.BitNumber = FindBitDifference(Receiving, Incoming)+1;
        return Incoming.BitNumber;
    }
    if(Incoming.BitNumber > Receiving.BitNumber){
        TNode *NextNode, *NewNode;
        if(IncBit){
            NextNode = Receiving.Right;
            try{Receiving.Right = new TNode;}
            catch(const std::bad_alloc &e){
                std::cout << "ERROR: can't allocate\n";
                return -2;
            }
            NewNode = Receiving.Right;
        }
        else{
            NextNode = Receiving.Left;
            try{Receiving.Left = new TNode;}
            catch(const std::bad_alloc &e){
                std::cout << "ERROR: can't allocate\n";
                return -2;
            }
            NewNode = Receiving.Left;
        }
        *NewNode = Incoming;
        if(GetBit(Incoming.BitNumber-1, Incoming.Key.size(), Incoming.Key)){
            NewNode->Right = NewNode;
            NewNode->Left = NextNode;
        }
        else{
            NewNode->Left = NewNode;
            NewNode->Right = NextNode;
        }
        Incoming.BitNumber = 0;
    }
    return Incoming.BitNumber;
}

int TPatricia::AddNode(KeyType& Key, ValueType Value){
    if(Root == nullptr){
        try{Root = new TNode;}
        catch(const std::bad_alloc &e){
            std::cout << "ERROR: can't allocate\n";
            return -2;
        }
        Root->BitNumber = 0;
        Root->Key = Key;
        Root->Value = Value;
        Root->Left = Root;
        Root->Right = nullptr;
        return 0;
    }
    else{
        TNode node;
        node.Key = Key;
        node.Value = Value;
        return InsertNode(*Root, node);
    }
}

int TPatricia::DeleteNode(KeyType& Key){
    if(Root == nullptr) return 0;
    bool eqty, gb;
    int i = 0;
    TNode * grandParent = nullptr, * parent, * child, * descendant, * descendantSon;
    parent = Root;
    child = Root->Left;
    while(parent->BitNumber < child->BitNumber){
        grandParent = parent;
        parent = child;
        child = (GetBit(child->BitNumber-1, Key.size(), Key)) ? child->Right : child->Left;
    }
    eqty = (child->Key == Key);
    if(!eqty) return 0;
    if(grandParent == nullptr){
        delete parent;
        Root = nullptr;
        return 1;
    }
    child->Key = parent->Key;
    child->Value = parent->Value;
    if(!(parent == child)){
        descendant = Root;
        descendantSon = Root->Left;
        while(descendant->BitNumber < descendantSon->BitNumber){
            descendant = descendantSon;
            descendantSon = (gb = GetBit(descendantSon->BitNumber-1, parent->Key.size(), parent->Key)) ? descendantSon->Right : descendantSon->Left;
        }
        if(gb){
            descendant->Right = child;
        }
        else{
            descendant->Left = child;
        }
    }
    if (grandParent->Right == parent){
        grandParent->Right = (parent->Right == child)? parent->Left : parent->Right;
    }
    else{
        grandParent->Left = (parent->Right == child)? parent->Left : parent->Right;
    }
    delete parent;
    return 1;
}

TPatricia::ValueType* TPatricia::NodeSearch(TNode &Tree, KeyType &Key, int PreviousBitNumber){
    if(PreviousBitNumber < Tree.BitNumber){
        if(GetBit(Tree.BitNumber-1, Key.size(), Key)){
            return NodeSearch(*(Tree.Right), Key, Tree.BitNumber);
        }
        else{
            return NodeSearch(*(Tree.Left), Key, Tree.BitNumber);
        }
    }
    else{
        if(Key == Tree.Key){
            return &Tree.Value;
        }
    }
    return nullptr;
}

TPatricia::ValueType* TPatricia::FindNode(KeyType &Key){
    ValueType* PointerToValue=nullptr;
    if(Root!=nullptr){
        PointerToValue = NodeSearch(*(Root->Left), Key, 0);
        return PointerToValue;
    }
    return PointerToValue;
}



void TPatricia::SaveTree(TNode* node, FILE * f){
    bool hasLeftChild, hasRightChild;
    fwrite(&(node->Value), sizeof(node->Value), 1, f);
    fwrite(&(node->BitNumber), sizeof(node->BitNumber), 1, f);
    int size = node->Key.size();
    fwrite(&size, sizeof(size), 1, f);
    fwrite(node->Key.cstr(), sizeof(KeyType::ValueType)*size, 1, f);
    hasLeftChild = (node->BitNumber < node->Left->BitNumber);
    fwrite(&hasLeftChild, sizeof(bool), 1, f);
    hasRightChild = (node->Right == nullptr) ? false : (node->BitNumber < node->Right->BitNumber);
    fwrite(&hasRightChild, sizeof(bool), 1, f);
    if(hasLeftChild) SaveTree(node->Left, f);
    if(hasRightChild) SaveTree(node->Right, f);
}

int TPatricia::SaveInFile(KeyType name){
    FILE* f = fopen(name.cstr(), "wb");
    if(f != nullptr){
        fwrite(FILE_HEADER, sizeof(char)*SIZE_OF_HEADER, 1, f);
        if(Root != nullptr) SaveTree(Root, f);
        fclose(f);
        return 1;
    }
    return 0;
}

void TPatricia::RemoveTree(TNode* node){
    if(node != nullptr){
        if(node->BitNumber < node->Left->BitNumber) RemoveTree(node->Left);
        if(node->Right != nullptr){
            if(node->BitNumber < node->Right->BitNumber){
                RemoveTree(node->Right);
            }
        }
        delete node;
    }
}

TPatricia::TNode* TPatricia::LoadTree(TNode * parent, bool isRight, FILE * f){
    TNode *added = new TNode;
    bool hasLeftChild, hasRightChild;
    //reading

    if(fread(&(added->Value), sizeof(added->Value), 1, f) > 0){
        fread(&(added->BitNumber), sizeof(added->BitNumber), 1, f);
        int size;
        fread(&size, sizeof(size), 1, f);
        char * tmpStr = new char[size+1];
        fread(tmpStr, sizeof(KeyType::ValueType)*size, 1, f);
        tmpStr[size]='\0';
        added->Key = tmpStr;
        fread(&hasLeftChild, sizeof(bool), 1, f);
        fread(&hasRightChild, sizeof(bool), 1, f);
    }
    else return parent;
    
    //childbirth
    if(parent == nullptr){
        if(hasLeftChild);
        if(hasRightChild);
        added->Left = added;
        added->Right = nullptr;
    }
    else if(isRight){
        if(GetBit(added->BitNumber-1, added->Key.size(), added->Key)){
            added->Right = added;
            added->Left = parent->Right;
        }
        else{
            added->Left = added;
            added->Right = parent->Right;
        }
        parent->Right = added;
    }
    else{
        if(GetBit(added->BitNumber-1, added->Key.size(), added->Key)){
            added->Right = added;
            added->Left = parent->Left;
        }
        else{
            added->Left = added;
            added->Right = parent->Left;
        }
        parent->Left = added;
    }
    if(hasLeftChild) added->Left = LoadTree(added, 0, f);
    if(hasRightChild) added->Right = LoadTree(added, 1, f);
    return added;
}

int TPatricia::LoadFromFile(KeyType name){
    FILE* f = fopen(name.cstr(), "rb");
    if(f != nullptr){
        char b[SIZE_OF_HEADER+1];
        fread(b, SIZE_OF_HEADER , 1, f);
        b[SIZE_OF_HEADER]='\0';
        if(StringsEqual(b, FILE_HEADER)){
            Clear();
            if(Root == nullptr) Root = LoadTree(Root, 0, f);
            fclose(f);
            return 1;
        }
        fclose(f);
    }
    return 0;
}

void TPatricia::Clear(){
    if(Root != nullptr){
        RemoveTree(Root);
        Root = nullptr;
    }
}

TPatricia::~TPatricia(){
    Clear();
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    TPatricia tree;
    TString Key;
    unsigned long long Value;
    while(std::cin>>Key){
        switch(Key[0]){
            case '+':
                std::cin>>Key>>Value;
                if(tree.AddNode(Key, Value) == 0){
                    std::cout << "OK\n";
                }
                else{
                    std::cout<< "Exist\n";
                }
                break;
            case '-':
                std::cin >> Key;
                if(tree.DeleteNode(Key)){
                    std::cout << "OK\n";
                }
                else{
                    std::cout << "NoSuchWord\n";
                }
                break;
            case '!':
                std::cin >> Key;
                if(Key == "save"){
                    std::cin >> Key;
                    if(tree.SaveInFile(Key)){
                        std::cout << "OK\n";
                    }
                    else{
                        std::cout << "ERROR: can't open file\n";
                    }
                }
                else if(Key == "load"){
                    std::cin>>Key;
                    if(tree.LoadFromFile(Key)){
                        std::cout << "OK\n";
                    }
                    else{
                        std::cout << "ERROR: can't open file";
                    }
                }
                break;
            default:
                unsigned long long int *value = tree.FindNode(Key);
                if(value != nullptr) std::cout << "OK: " << *value <<"\n";
                else std::cout << "NoSuchWord\n";
                break;
        }
    }
}
