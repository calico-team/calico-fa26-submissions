#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define V vector<int>
#define Vll vector<ll>

signed main() {
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int T; cin >> T;
    while(T-- > 0) {
        int n, k; cin >> n >> k;
        vector<char> a(n);
        vector<char> ans(n, '_');
        bool good = false;
        for(int i = 0; i < k; i++) cin >> a[i];
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < n; j++) {
                if(ans[j] == '_') cout << a[i];
                else cout << ans[j];
            }
            cout << endl;
            string s; cin >> s;
            if(s == "CORRECT") {
                good = true;
                break;
            }
            else {
                for(int i = 0; i < n; i++) {
                    if(s[i] != '_') ans[i] = s[i];
                }
            }
            if(good) break;
        }
    }
}