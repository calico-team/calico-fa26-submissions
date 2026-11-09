#include <bits/stdc++.h>
using namespace std;

void solve(){
                string s ; cin >> s;
        if(s.find("write_me") != string::npos){
              s += "make_it_sound_human";
           
        }else if(s.find("solve")!= string::npos){
              s += "make_no_mistakes"; 
            
         }
        else if(s.find("what_is")!= string::npos){
              s += "do_not_hallucinate";
           
        }else{
            s+="thank_you";
        }

    cout << s << endl;


}
int main(){

    int t; cin >> t;
    while(t--){
        solve();

    }



    return  0;
}