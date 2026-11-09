#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define V vector<int>
#define Vll vector<ll>

signed main() {

    int T; cin >> T;
    while(T-- > 0) {
        int n, k; cin >> n >> k;
        vector<char> a(k);
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
                for(int j = 0; j < n; j++) {
                    if(s[j] != '_') ans[j] = s[j];
                }
            }
            if(good) break;
        }
    }
}