#include <bits/stdc++.h>
using namespace std;

void solve(){
    string s;
    cin >> s;
    int n = s.length();
    vector<string> a = {"write_me", "what_is", "solve"};
    vector<string> b = {"make_it_sound_human", "do_not_hallucinate", "make_no_mistakes"};
    bool seen = false;
    for(int i=0; i<n; i++) for(int j=0; j<3; j++) if(i + a[j].length() <= n && s.substr(i, a[j].length()) == a[j]) s += b[j], seen = true;
    if(!seen) s += "thank_you";
    cout << s << '\n';
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--) solve();
}