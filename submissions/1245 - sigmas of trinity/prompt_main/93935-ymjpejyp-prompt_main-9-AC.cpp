#include <bits/stdc++.h>

using namespace std;

int main(){
    ios::sync_with_stdio(0); cin.tie(0);
    int T;
    cin >> T;
    while(T--){
        string S;
        cin >> S;
        if(S.find("write_me") != string::npos){
            cout << S << "make_it_sound_human" << endl;
        }
        else if(S.find("what_is") != string::npos){
            cout << S << "do_not_hallucinate" << endl;
        }
        else if(S.find("solve") != string::npos){
            cout << S << "make_no_mistakes" << endl;
        }
        else{
            cout << S << "thank_you" << endl;
        }
    }
}