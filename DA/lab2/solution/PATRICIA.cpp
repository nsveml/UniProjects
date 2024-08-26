#include<stdio.h>
#include<stdlib.h>

#include"PATRICIA.hpp"

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
        if(i == Incoming.Key.Size() || i == Receiving.Key.Size()){
            break;
        }
    }
    if(i == Incoming.Key.Size() && i == Receiving.Key.Size()){
        FBD = -2;
    }
    else if((i <= Incoming.Key.Size()) && (i <= Receiving.Key.Size())){
        i*=sizeof(char)*8;
        for(int j = 0; j < sizeof(char)*8; j++){
            int a, b;
            a = GetBit(i + j, Receiving.Key.Size(), Receiving.Key);
            b = GetBit(i + j, Incoming.Key.Size(), Incoming.Key);
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
        else if( IncBit = GetBit(Receiving.BitNumber-1, Incoming.Key.Size(), Incoming.Key)){
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
            Receiving.Right = new TNode;
            NewNode = Receiving.Right;
        }
        else{
            NextNode = Receiving.Left;
            Receiving.Left = new TNode;
            NewNode = Receiving.Left;
        }
        *NewNode = Incoming;
        if(GetBit(Incoming.BitNumber-1, Incoming.Key.Size(), Incoming.Key)){
            NewNode->Right = NewNode;
            NewNode->Left = NextNode;
        }
        else{
            NewNode->Left = NewNode;
            NewNode->Right = NextNode;
        }
        TreeSize++;
        Incoming.BitNumber = 0;
    }
    return Incoming.BitNumber;
}

int TPatricia::AddNode(KeyType& Key, ValueType Value){
    if(Root == nullptr){
        TreeSize++;
        Root = new TNode;
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
        child = (GetBit(child->BitNumber-1, Key.Size(), Key)) ? child->Right : child->Left;
    }
    eqty = (child->Key == Key);
    if(!eqty) return 0;
    if((grandParent == nullptr)){
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
            descendantSon = (gb = GetBit(descendantSon->BitNumber-1, parent->Key.Size(), parent->Key)) ? descendantSon->Right : descendantSon->Left;
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
    TreeSize--;
    return 1;
}

TPatricia::ValueType* TPatricia::NodeSearch(TNode &Tree, KeyType &Key, int PreviousBitNumber){
    if(PreviousBitNumber < Tree.BitNumber){
        if(GetBit(Tree.BitNumber-1, Key.Size(), Key)){
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
    int Size = node->Key.Size();
    fwrite(&Size, sizeof(Size), 1, f);
    fwrite(node->Key.cstr(), sizeof(KeyType::ValueType)*Size, 1, f);
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
        TreeSize++;
        fread(&(added->BitNumber), sizeof(added->BitNumber), 1, f);
        int size;
        fread(&size, sizeof(size), 1, f);
        char * tmpStr = new char[size+1];
        fread(tmpStr, sizeof(KeyType::ValueType)*size, 1, f);
        tmpStr[size]='\0';
        added->Key = std::move(tmpStr);
        fread(&hasLeftChild, sizeof(bool), 1, f);
        fread(&hasRightChild, sizeof(bool), 1, f);
    }
    else{
        delete added;
        return nullptr;
    }
    
    
    //childbirth
    if(parent == nullptr){
        if(hasLeftChild);
        if(hasRightChild);
        added->Left = added;
        added->Right = nullptr;
    }
    else if(isRight){
        if(GetBit(added->BitNumber-1, added->Key.Size(), added->Key)){
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
        if(GetBit(added->BitNumber-1, added->Key.Size(), added->Key)){
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
        if(fread(b, SIZE_OF_HEADER , 1, f) == 0){
            fclose(f);
            return 2;
        }
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
        TreeSize = 0ull;
        Root = nullptr;
    }
}

TPatricia::~TPatricia(){
    Clear();
}
