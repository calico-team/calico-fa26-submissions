#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#define all(x) x.begin(), x.end()

void solve() {
    string S; cin >> S; 

    if (S.find("write_me") != string::npos) {
        cout << S + "make_it_sound_human\n"; 
    }
    else if (S.find("what_is") != string::npos) {
        cout << S + "do_not_hallucinate\n"; 
    }
    else if (S.find("solve") != string::npos) {
        cout << S + "make_no_mistakes\n";
    }
    else {
        cout << S + "thank_you\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t; 
    while(t--)
        solve();
}