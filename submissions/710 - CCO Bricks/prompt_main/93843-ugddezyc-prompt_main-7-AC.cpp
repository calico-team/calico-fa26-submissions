#include <bits/stdc++.h>
#define int long long
#define pii pair<int, int>
using namespace std;
// const int MOD = 998'244'353;
// const int MOD = 1e9 + 7;

void solve() {
    string s; cin >> s;

    if (s.find("write_me") != variant_npos) s += "make_it_sound_human";
    else if (s.find("what_is") != variant_npos) s += "do_not_hallucinate";
    else if (s.find("solve") != variant_npos) s += "make_no_mistakes";
    else s += "thank_you";

    cout << s << "\n";
}

signed main() {
    cin.sync_with_stdio(0);
    cin.tie(0);

    int t; cin >> t;
    while (t--) solve();


    return 0;
}