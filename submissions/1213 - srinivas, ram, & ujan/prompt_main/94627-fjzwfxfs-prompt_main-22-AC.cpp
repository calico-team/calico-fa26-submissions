// Source: https://usaco.guide/general/io
//gabriel liu

#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
    cin >> t;
    string a = "write_me";
    string b = "what_is";
    string c = "solve";
    string A = "make_it_sound_human";
    string B = "do_not_hallucinate";
    string C = "make_no_mistakes";
    string D = "thank_you";
    while(t--){
        string n;
        cin >> n;
        int yes;
        if(n.find("write_me") != string::npos){
            cout << n + A << '\n';
        }else if(n.find("what_is") != string::npos){
            cout << n + B << '\n';
        }else if(n.find("solve") != string::npos){
            cout << n + C << '\n';
        }else{
            cout << n + D << '\n';
        }
    }
}
