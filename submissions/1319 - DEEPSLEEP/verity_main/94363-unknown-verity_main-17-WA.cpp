#include<bits/stdc++.h>
using namespace std;
string a = "[###OREO###]";
string b = " [--------] "; 
int T;
int main(){
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        for(int i = 0; i < s.size(); ++i){
            if(s[i] == 'O') cout << a << endl;
            else if(s[i] == 'R') cout << b << endl;
            else if(s[i] == '&') cout << endl;
        }
    }
    return 0;
}/*

*/