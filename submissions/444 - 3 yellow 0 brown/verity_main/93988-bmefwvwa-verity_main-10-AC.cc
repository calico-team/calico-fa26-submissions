#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define DBG(X)
#else
#define DBG(X) println(#X": {}", X)
#endif

#define int int64_t

void ac() {
    int n, k; cin >> n >> k;    
    string s(k, '_');
    for (char &c : s) cin >> c;
    string cur(n, '_');
    for (char &c : s) {
        string guess = cur;
        for (char &x : guess) if (x == '_') x = c;
        cout << guess << endl;
        cin >> cur;
        if (cur == "CORRECT") return;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int t; cin >> t;
    while (t--) ac();
}