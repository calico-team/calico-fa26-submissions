#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

int t, n, k;
random_device rd;
mt19937 g(rd());

void casos() {
    string pa, r;
    vector<vector<char>> mango(t);

    for(int i=0; i<t; i++){
        cin >> n >> k;
        cin.ignore();
        getline(cin, pa);
        shuffle(pa.begin(), pa.end(), g);

        for(char c : pa) {
            if(c!=' '){
                mango[i].push_back(c);
            }
        }
    }

    for(int e=0; e<1; e++){
        for(char c : mango[e]) {
            cout << c;
        }
        cout << endl;
        
        while(cin >> r){
            if (r=="CORRECT") {
                break;
            } 
            
            for (char c : mango[e]) {
                cout << c;
            }
            cout << endl;
        }
    }
}
int main() {
    cin >> t;
    for(int i=0; i<t; i++){
        casos();
    }
}