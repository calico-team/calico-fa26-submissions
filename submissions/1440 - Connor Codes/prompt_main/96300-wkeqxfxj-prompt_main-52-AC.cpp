#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    // freopen("XXXXXXX.in", "r", stdin);
    // freopen("XXXXXXX.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    ll T;
    cin >> T;
    while(T--){
        string s;
        cin >> s;
        string write_me = "write_me";
        string what_is = "what_is";
        string solve = "solve";
        bool work = false;
        for(ll i = 0; i < s.size(); i++){
            bool check = true;
            if(i+write_me.size()-1 < s.size()){
                for(ll j = 0; j < write_me.size(); j++){
                    if(s[i+j] != write_me[j]){
                        check = false;
                    }
                }
                if(check){
                    cout << s << "make_it_sound_human" << endl;
                    work = true;
                    break;
                }
            }
            check = true;
            if(i+what_is.size()-1 < s.size()){
                for(ll j = 0; j < what_is.size(); j++){
                    if(s[i+j] != what_is[j]){
                        check = false;
                    }
                }
                if(check){
                    cout << s << "do_not_hallucinate" << endl;
                    work = true;
                    break;
                }
            }
            check = true;
            if(i+solve.size()-1 < s.size()){
                for(ll j = 0; j < solve.size(); j++){
                    if(s[i+j] != solve[j]){
                        check = false;
                    }
                }
                if(check){
                    cout << s << "make_no_mistakes"  << endl;
                    work = true;
                    break;
                }
            }
        }
        if(!work){
            cout << s << "thank_you" << endl;
        }
        
    }
}