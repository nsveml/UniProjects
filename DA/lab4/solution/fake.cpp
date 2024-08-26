#include<iostream>
#include<string>
#include<map>

using namespace std;

int main(){
    ios::sync_with_stdio(false);
    int field=2, count=0, figure = -1;
    char column;
    string inp;
    map<string, int> kidmapping{{"pawn", 0}, {"rook", 1}, {"knight", 2}, {"bishop", 3}, {"queen", 4}, {"king", 5}};
    while(true){
            
        cin >> inp;
        count++;

    	if(inp == "black"){
        	field = 1;
        	figure = -1;
        }
    	else if(inp == "white"){
        	field = 0;
        	figure = -1;
        }
        else{
            if(figure != kidmapping[inp]){
                figure = kidmapping[inp];
            }
            else{
                count--;
                cout << "? U" << endl;
                cin >> inp;
                cout << "? U" << endl;
                cin >> inp;
                if(inp == "black") field = 1;
                else if(inp == "white") field = 0;
            }
        }

        if(field == 0 && figure > 0){
            cout << "! ";
            if(figure == 1){
                cout << 'h';
            }
            else if(figure == 2){
                cout << 'b';
            }
            else if(figure == 3){
                cout << 'f';
            }
            else if(figure == 4){
                cout << 'd';
            }
            cout << count << endl;
            break;
        }
        else if(field == 1 && figure > 0){
            cout << "! ";
            if(figure == 1){
                cout << 'a';
            }
            else if(figure == 2){
                cout << 'g';
            }
            else if(figure == 3){
                cout << 'c';
            }
            else if(figure == 5){
                cout << 'e';
            }
            cout << count << endl;
            break;
        }

        cout << "? D" << endl;
    }
    
}