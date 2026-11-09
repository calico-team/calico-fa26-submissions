#pragma GCC optimize("O3,unroll-loops")

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    string s; cin >> s;
    if (s.find("write_me") != string::npos) {
        s += "make_it_sound_human";
    }
    else if (s.find("what_is") != string::npos) {
        s += "do_not_hallucinate";
    }
    else if (s.find("solve") != string::npos) {
        s += "make_no_mistakes";
    }
    else {
        s += "thank_you";
    }
    cout << s << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) solve();

    return 0;
}