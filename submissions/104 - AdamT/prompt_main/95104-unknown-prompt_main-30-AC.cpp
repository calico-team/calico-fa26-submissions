#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "timer.h"
#else
struct Timer {
    Timer(string_view = "") {}
};
#endif

#ifdef DEBUG
#include "dbg.h"
#else
#define dbg(...) __VA_ARGS__
#endif

void solve() {
    string s;
    cin >> s;
    if (s.find("write_me") != string::npos) {
        s += "make_it_sound_human";
    } else if (s.find("what_is") != string::npos) {
        s += "do_not_hallucinate";
    } else if (s.find("solve") != string::npos) {
        s += "make_no_mistakes";
    } else {
        s += "thank_you";
    }
    cout << s << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    cout << flush;
    return 0;
}
