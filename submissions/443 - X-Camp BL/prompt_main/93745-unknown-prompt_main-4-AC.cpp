#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
void solve() {
    string s; cin >> s;
    if (s.find("write_me") != string::npos) {
        s += "make_it_sound_human";
    } else if (s.find("what_is") != string::npos) {
        s += "do_not_hallucinate";
    } else if (s.find("solve") != string::npos) {
        s += "make_no_mistakes";
    } else {
        s += "thank_you";
    }
    cout << s << endl;
}
int main() {
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
}