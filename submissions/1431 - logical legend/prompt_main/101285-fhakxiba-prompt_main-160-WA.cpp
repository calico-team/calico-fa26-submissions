#include <bits/stdc++.h>
using namespace std;

void solve(){
 string s ; cin >> s;
            if(s.find("write_me") != string::npos){
            cout << s << "make_it_sound_human" << endl;
           return;
        }if(s.find("solve")!= string::npos){
            cout << s << "make_no_mistakes" << endl; 
            return;
         }
        if(s.find("what_is")!= string::npos){
            cout << s << "do_not_hallucinate" << endl;
           return;
        }cout << s << "thank_you";



}
int main(){

    int t; cin >> t;
    while(t--){
        solve();

    }



    return  0;
}