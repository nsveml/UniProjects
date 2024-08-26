#include<iostream>

#include "PATRICIA.cpp"

int main(){
    //std::ios::sync_with_stdio(false);
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
        std::cout<<'\n';
    }
}