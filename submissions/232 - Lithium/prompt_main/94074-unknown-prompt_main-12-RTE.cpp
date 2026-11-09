#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    string s;
    cin >> s;
    for (int j = 0; j <= s.size() - 5; j++) {
        if (j <= s.size() - 8 && s.substr(j, 8) == "write_me") {
            cout << s + "make_it_sound_human\n";
            return;
        }
        if (j <= s.size() - 7 && s.substr(j, 7) == "what_is") {
            cout << s + "do_not_hallucinate\n";
            return;
        }
        if (s.substr(j, 5) == "solve") {
            cout << s + "make_no_mistakes\n";
            return;
        }
    }
    cout << s + "thank_you\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        solve();
    }
}