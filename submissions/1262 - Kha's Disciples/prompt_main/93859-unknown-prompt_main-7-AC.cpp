// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

void solve() {
    string s;
    cin >> s;
    if (s.find("write_me") != string::npos) {
        cout << s.append("make_it_sound_human") << endl;
    } else if (s.find("what_is") != string::npos) {
        cout << s.append("do_not_hallucinate") << endl;
    } else if (s.find("solve") != string::npos) {
        cout << s.append("make_no_mistakes") << endl;
    } else {
        cout << s.append("thank_you") << endl;
    }
}

int main() {
	int s;
    cin >> s;
    for (int i = 0; i < s; i++) {
        solve();
    }
}
