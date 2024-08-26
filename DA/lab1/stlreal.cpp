#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<time.h>

using namespace std;

int main(){
    pair<string, string> para;
    vector<pair<string, string>> vec;
    ios::sync_with_stdio(false);
    while(getline(cin, para.first)){
        getline(cin, para.second);
        vec.push_back(para);
    }
    stable_sort(vec.begin(), vec.end());
    /*for(int i = 0; i < vec.size(); i++){
        cout << vec[i].first << ' ' << vec[i].second << '\n';
    }*/
}