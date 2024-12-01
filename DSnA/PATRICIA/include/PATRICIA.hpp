#pragma once
#include<iostream>
#include "string.hpp"



class TPatricia {

    public:

        static const char FILE_HEADER [];
        static const int SIZE_OF_HEADER;

        using KeyType = TString;
        using ValueType = unsigned long long;

        TPatricia(){
            TreeSize = 0;
            Root = nullptr;
        }
        void Clear();
        int AddNode(KeyType &, ValueType);
        
        int DeleteNode(KeyType&);
        
        ValueType* FindNode(KeyType&);
        
        int SaveInFile(KeyType);
        
        int LoadFromFile(KeyType);
        
        unsigned long long GetSize(){
            return TreeSize;
        }

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
        unsigned long long TreeSize;

        void SaveTree(TNode *, FILE *);

        TNode*  LoadTree(TNode *, bool, FILE *);

        void RemoveTree(TNode*);
        
        bool GetBit(int, int,  KeyType&); 

        int FindBitDifference(TNode &, TNode &);
        
        int InsertNode(TNode &, TNode &);
        
        ValueType* NodeSearch(TNode &, KeyType&, int);
        
};
