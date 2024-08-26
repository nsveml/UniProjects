#include<iostream>
#include<unordered_map>
#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>
#include<iterator>

class TTrie{
    private:

    struct TTrieNode{
        std::unordered_map<unsigned int, TTrieNode *> links;
        TTrieNode * parent;
        TTrieNode * failure;
        TTrieNode * exit;
        unsigned int length;
        unsigned int number;
        unsigned int symb;

        TTrieNode(){
            symb = 0;
            parent = nullptr;
            failure = nullptr;
            exit = nullptr;
            length = 0;
            number = 0;
        }
    };        
        
    TTrieNode* root;

    TTrieNode* iter;

    unsigned int depth;
    unsigned int maxDepth;
    unsigned int quantity;

    public:

    TTrie(){
        root = new TTrieNode;
        iter = root;
        depth = 0;
        maxDepth = 0;
        quantity = 0;
    }

    void SaveWord(unsigned int& number){
        iter->number = number;
        iter->length = depth;
        iter = root;
        if(depth > maxDepth) maxDepth = depth;
        depth = 0;
    }

    void Add(unsigned int& key){
        if(iter->links.find(key) == iter->links.end()){
            iter->links[key] = new TTrieNode;
            iter->links[key]->parent = iter;
        }
        iter = iter->links[key];
        if(iter->parent == root){
            iter->failure = root;
        }
        iter->symb = key;
        depth++;
    }

    void EstConnectionsForLevel(const int& maxLevel, TTrieNode * curNode, int curLevel){
        if(curLevel != maxLevel ){
            for(const auto& someVertexPair : curNode->links) {
                EstConnectionsForLevel(maxLevel, someVertexPair.second, curLevel+1);
            }
        }
        if(curLevel == maxLevel){
            curNode->failure = curNode->parent;
            while(curNode->failure->failure != nullptr){
                curNode->failure = curNode->failure->failure;
                if(curNode->failure->links.find(curNode->symb) != curNode->failure->links.end()){
                    curNode->failure = curNode->failure->links[curNode->symb];
                    break;
                }
            }
            if(curNode->failure == nullptr) curNode->failure = root;
            if(curNode->failure->number != 0){
                curNode->exit = curNode->failure;
            }
            else if(curNode->failure->exit != nullptr) curNode->exit = curNode->failure->exit;
        }
    }

    void EstConnections() {
        for(unsigned int i = 2; i <= maxDepth; i++){
            EstConnectionsForLevel(i, root, 0);
        }
    }
    

    void Find(const std::vector<unsigned int>& text, std::vector<long long>& occur) {
        TTrieNode* exitPointer;
        for(long unsigned int i = 0; i < text.size(); i++){
            if(iter->links.find(text[i]) != iter->links.end()){
                iter = iter->links[text[i]];
            }
            else{
                while(iter != root){
                    iter = iter->failure;
                    if(iter->links.find(text[i]) != iter->links.end()){
                        iter = iter->links[text[i]];
                        break;
                    }
                }
            }
            exitPointer = iter->exit;
            while(exitPointer != nullptr){
                occur.push_back(i+1);
                occur.push_back(exitPointer->length);
                occur.push_back(exitPointer->number);
                exitPointer = exitPointer->exit;
            }
            if(iter->length != 0){
                occur.push_back(i+1);
                occur.push_back(iter->length);
                occur.push_back(iter->number);
            }
        }


    }
    void Match(const std::vector<unsigned int>& text, std::vector<long long>& occur) {
        iter = root;
        Find(text, occur);
    }

    void clearall(TTrieNode * curNode){
        for(auto& someVertexPair : curNode->links){
            clearall(someVertexPair.second);
            delete someVertexPair.second;
        }
    }

    ~TTrie(){
        clearall(root);
        delete root;
    }

};

int main(){
    std::ios::sync_with_stdio(false);
    TTrie trie;
    unsigned int number, wordNumber = 0, lineNumber = 1;
    std::string str;
    std::string rts;
    std::stringstream strstr;
    
    while(getline(std::cin, str)){

        strstr.str(str);
        while(strstr >> number){
            wordNumber++;
            trie.Add(number);
        }
        if(wordNumber == 0) break;
        wordNumber = 0;
        strstr.clear();
        trie.SaveWord(lineNumber);
        lineNumber++;

    }
    trie.EstConnections();
    std::vector<unsigned int> text;
    std::vector <unsigned int> lineEndings;
    lineEndings.push_back(0);
    while(getline(std::cin, str)) {
        char* p = (char*)str.c_str();
        char* end = p;
        while (true) {
            int cur = strtol(p, &end, 10);
            if (end == p) {
                break;
            }
            p = end;
            text.push_back(cur);
        }
        lineEndings.push_back(text.size());
    }
    std::vector<long long> occur;
    trie.Match(text, occur);
    for(unsigned int i = 0; i < occur.size(); i+=3){
        auto lower = std::lower_bound(lineEndings.begin(), lineEndings.end(), occur[i]-occur[i+1]+1);
        if(lower != lineEndings.end()) lineNumber = std::distance(lineEndings.begin(), lower);
        std::cout << lineNumber << ", " << occur[i]-occur[i+1]+1-lineEndings[lineNumber-1] << ", " << occur[i+2] << '\n';
    }
}