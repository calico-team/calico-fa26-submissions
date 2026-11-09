#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    string s; cin >> s;
    cout << s;

    if (s.find("write_me") != string::npos) {
        cout << "make_it_sound_human";
    } else if (s.find("what_is") != string::npos) {
        cout << "do_not_hallucinate";
    } else if (s.find("solve") != string::npos) {
        cout << "make_no_mistakes";
    } else cout << "thank_you";
    
    cout << endl;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}