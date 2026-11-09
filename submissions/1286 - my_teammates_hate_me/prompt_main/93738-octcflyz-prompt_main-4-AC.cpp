#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

/** for blitz */
// ifstream cin("input.txt");
// ofstream cout("output.txt");

void solve() {
    string s;
    cin >> s;
    
    if (s.find("write_me") != string::npos) {
        cout << s + "make_it_sound_human\n";
        return;
    }
    if (s.find("what_is") != string::npos) {
        cout << s + "do_not_hallucinate\n";
        return;
    }
    if (s.find("solve") != string::npos) {
        cout << s + "make_no_mistakes\n";
        return;
    }
    cout << s + "thank_you\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}