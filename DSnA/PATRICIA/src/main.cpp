#include<iostream>

#include "PATRICIA.hpp"

int main(){
    //std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int a;
    TPatricia tree;
    TString Key(256);
    unsigned long long Value;
    unsigned long long Size;
    while(std::cin>>Key){
        switch(Key[0]){
            case '+':
                std::cin>>Key>>Value;
                Key.ToLower();
                try {
                    a = tree.AddNode(Key, Value);
                }
                catch(const std::bad_alloc& e) {
                    std::cout << "ERROR: bad_alloc\n";
                    break;
                }
                if( a == 0){
                    ++Size;
                    std::cout << "OK\n";
                }
                else{
                    std::cout << "Exist\n";
                }
                break;
            case '-':
                std::cin >> Key;
                Key.ToLower();
                if(tree.DeleteNode(Key)){
                    --Size;
                    std::cout << "OK\n";
                }
                else{
                    std::cout << "NoSuchWord\n";
                }
                break;
            case '!':
                std::cin >> Key;
                if(Key == "Save"){
                    std::cin >> Key;
                    if(tree.SaveInFile(Key)){
                        std::cout << "OK\n";
                    }
                    else{
                        std::cout << "ERROR: can't open file\n";
                    }
                }
                else if(Key == "Load"){
                    std::cin>>Key;
                    try {
                        a = tree.LoadFromFile(Key);
                        if( a == 1){
                            //std::cout << tree.GetSize() << '\n';
                            std::cout << "OK\n";
                        }
                        else if(a == 0){
                            std::cout << "ERROR: can't open file\n";
                        }
                        else if(a == 2){
                            std::cout << "ERROR: can't find PATRICIA\n";
                        }
                    }
                    catch (const std::bad_alloc& e) {
                        std::cout << "ERROR: can't allocate memory\n";
                    }
                }
                break;
            default:
                Key.ToLower();
                unsigned long long int *value = tree.FindNode(Key);
                if(value != nullptr) std::cout << "OK: " << *value <<"\n";
                else std::cout << "NoSuchWord\n";
                break;
        }
    }
    return 0;
}