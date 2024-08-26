#include<iostream>
#include<algorithm>
#include<string>
#include<map>

void str_tolower(std::string& s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return std::tolower(c); });
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::map<std::string, unsigned long long> tree;
    std::string Key(257, '\0');
    unsigned long long Value;
    std::map <std::string, unsigned long long>::iterator it = tree.begin();
    while(std::cin>>Key){
        switch(Key[0]){
            case '+':
                std::cin>>Key>>Value;
                str_tolower(Key);
                
                if(tree.find(Key) == tree.end()){
                    tree[Key] = Value;
                    std::cout << "OK\n";
                }
                else{
                    std::cout << "Exist\n";
                }
                break;
            case '-':
                std::cin >> Key;
                str_tolower(Key);
                it = tree.find(Key);
                if( it != tree.end()){
                    tree.erase(it);
                    std::cout << "OK\n";
                }
                else{
                    std::cout << "NoSuchWord\n";
                }
                break;
            default:
                str_tolower(Key);
                if(tree.find(Key) != tree.end()) std::cout << "OK: " << tree[Key] <<"\n";
                else std::cout << "NoSuchWord\n";
                break;
        }
    }
    return 0;
}