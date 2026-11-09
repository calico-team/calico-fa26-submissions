#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;
    vector<char> a(k);
    for (int i = 0; i < k; i++) cin >> a[i];
    
    string s(n, '_');
    for (int r = 0; ; r++) {
        string g = "";
        for (int i = 0; i < n; i++) {
            g += (s[i] != '_' ? s[i] : a[(i + r) % k]);
        }
        cout << g << endl;

        string res;
        cin >> res;
        if (res == "CORRECT") break;
        
        for (int i = 0; i < n; i++) {
            if (res[i] != '_') s[i] = res[i];
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
