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
        vector<string> words;
        string x = "";
        for(ll i = 0; i < s.size();i++){
            if(s[i] == '_'){
                words.push_back(x);
                x = "";
                continue;
            }
            x += s[i];
        }
        
        if(words.size() == 1){
            if(words[0] == "solve"){
                cout <<  s << "make_no_mistakes" << endl;
                continue;
            }
            cout << s << "thank_you" << endl;
            continue;
        }
        bool check = false;
        for(ll i = 0; i< words.size()-1; i++){
            if(words[i] == "write" and words[i+1] == "me"){
                cout << s << "make_it_sound_human" << endl;
                check = true;
                break;
            }else if(words[i] == "what" and words[i+1] == "is"){
                cout << s << "do_not_hallucinate" << endl;
                check = true;
                break;
            } else if(words[i] == "solve"){
                cout <<  s << "make_no_mistakes" << endl;
                check = true;
                break;
            }
        }
        if(!check){
            cout << s << "thank_you" << endl;
        }
    }
}