#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        string s;
        cin >> s;
        if(s.find("write_me") != string::npos){
            s += "make_it_sound_human";
        }else if(s.find("what_is") != string::npos){
            s += "do_not_hallucinate";
        }else if(s.find("solve") != string::npos){
            s += "make_no_mistakes";
        }else{
            s += "thank_you";
        }
        cout << s << '\n';
    }
}
