#include<bits/stdc++.h>
using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    vector<char> s(k+1);
    for(int i=1;i<=k;i++) cin >> s[i];

    string ans = "";
    for(int i=1;i<=n;i++) ans+="_";
    for(int i=1;i<=k;i++) {
        for(int j=0;j<n;j++) {
            if(ans[j] == '_') ans[j] = s[i];
        }

        cout << ans << "\n" << flush;
        string p; cin >> p;
        if(p == "CORRECT") return;
        ans = p;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int t = 1; cin >> t;
    while(t--) solve();
}