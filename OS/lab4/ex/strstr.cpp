#include <iostream>
#include <sstream>

int main() {
    std::stringstream str, str2;
    std::string word1, word2, word3, word4;
    str << "word1 word2\nword3 word4\n";
    char line[255];
    while(str.getline(line, 255)) {
        str2 << line;
        //std::cout << line << "\n";
        if (str2 >> word1) {
            std::cout << word1 << "\n";
        }
        else {
            std::cout << "Fail\n";
        }
        str2.clear();
        if (str2 >> word1) {
            std::cout << word1 << "\n";
        }
        else {
            std::cout << "Fail\n";
        }
        str2.clear();
    }
}