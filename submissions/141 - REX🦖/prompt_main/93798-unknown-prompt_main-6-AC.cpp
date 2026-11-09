#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 7;

int t, n;
string s;

void solve(){

    cin >> s, n = s.size();
    bool f = 0;
    for(int i = 0; i < n; i ++){
        if(i + 7 < n){
            if(s.substr(i, 8) == "write_me"){
                s += "make_it_sound_human", f = 1;
                break;
            }
        }
        if(i + 6 < n){
            if(s.substr(i, 7) == "what_is"){
                s += "do_not_hallucinate", f = 1;
                break;
            }
        }
        if(i + 4 < n){
            if(s.substr(i, 5) == "solve"){
                s += "make_no_mistakes", f = 1;
                break;
            }
        }
    }
    if(!f) s += "thank_you";
    cout << s << '\n';

}

int main(){

    cin >> t;
    while(t --) solve();

    return 0;
}
