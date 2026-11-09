#include <bits/stdc++.h>
using namespace std;
#define int long long
void solve() {
    string s; cin >> s;
    int n=s.size();
    {
        string t="write_me";
        for (int i=0; i<n-t.size(); i++) {
            if (s.substr(i, t.size())==t) {
                cout << s << "make_it_sound_human" << "\n";
                return;
            }
        }
    }
    {
        string t="what_is";
        for (int i=0; i<n-t.size(); i++) {
            if (s.substr(i, t.size())==t) {
                cout << s << "do_not_hallucinate" << "\n";
                return;
            }
        }
    }
    {
        string t="solve";
        for (int i=0; i<n-t.size(); i++) {
            if (s.substr(i, t.size())==t) {
                cout << s << "make_no_mistakes" << "\n";
                return;
            }
        }
    }
    cout << s << "thank_you" << "\n";
    
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t; cin >> t;
    // int t=1;
    while (t--) solve();
}