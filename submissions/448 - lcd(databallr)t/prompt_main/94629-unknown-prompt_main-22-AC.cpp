#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back
#define all(x) x.begin(), x.end()

void solve() {
    int x;
    cin >> x;
    for (int i = 0; i < x; i++) {
        string s;
        cin >> s;
        if (s.find("write_me") != -1) {
            cout << s + "make_it_sound_human" << "\n";
        } else if (s.find("what_is") != -1) {
            cout << s + "do_not_hallucinate" << "\n";
        }
        else if (s.find("solve") != -1) {
            cout << s + "make_no_mistakes" << "\n";
        }
        else {
            cout << s + "thank_you" << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t = 1; 
    
    while (t--) {
        solve();
    }
    
    return 0;
}