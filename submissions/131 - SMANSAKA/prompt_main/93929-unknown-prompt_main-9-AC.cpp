#include <bits/stdc++.h>
using namespace std;

#define ll long long

void solve() {
    string s;
    cin >> s;
    
    // N kecil banget (<=100), string search O(N) aman sentosa ga bakal TLE
    if (s.find("write_me") != string::npos){
        s += "make_it_sound_human";
    } else if (s.find("what_is") !=string::npos) {
        s+= "do_not_hallucinate";
    } else if (s.find("solve") !=string::npos) {
        s +="make_no_mistakes";
    } else {
        s +="thank_you";
    }
    
    // bismillah AC 100 pt no corner case
    cout << s<< "\n";
}

int main() {
    // gasfast I/O
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}