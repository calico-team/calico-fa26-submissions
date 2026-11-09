#include <bits/stdc++.h>
using namespace std;
#define int long long
template<class T> inline void setmax(T& a, T b) {if (a < b) a = b;}
template<class T> inline void setmin(T& a, T b) {if (a > b) a = b;}
signed main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<char> v(n);
        map<char, int> m;
        for (int i = 0; i < n; i++) {
            cin >> v[i];
            m[v[i]] = i;
        }
        vector<int> a(n, 0);
        string s = string(n, '_');
        while (s != "CORRECT") {
            string c;
            for (int i = 0; i < n; i++) {
                if (s[i] != '_') {
                    cout << s[i];
                    c += s[i];
                    continue;
                }
                for (int j = 0; j < k; j++) {
                    if (a[i] & (1 << j)) continue;
                    cout << v[j];
                    c += v[j];
                    goto e;
                }
                e:;
            }
            cout << endl;
            cin >> s;
            if (s == "CORRECT") goto e2;
            for (int i = 0; i < n; i++) {
                if (s[i] != '_') continue;
                a[i] |= (1 << m[c[i]]);
            }
        }
        e2:;
    }
}