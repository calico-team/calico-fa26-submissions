#include <bits/stdc++.h>
using namespace std;
template<class T> inline void setmax(T& a, T b) {if (a < b) a = b;}
template<class T> inline void setmin(T& a, T b) {if (a > b) a = b;}
signed main() {
    int t = 1;
    cin >> t;
    while (t--) {
        int n, r;
        cin >> n >> r;
        vector<int> v(n);
        for (int& i : v) cin >> i;
        int sc = 2, lc = 0, pc = 0;
        for (int& i : v) {
            if (lc == 0) {
                sc--;
                lc = i;
            }
            else {
                int x = i - lc;
                sc += x / r;
                pc += x % r;
                if (pc > r) {
                    pc %= r;
                    sc++;
                }
                sc = min((int)sc, 2);
                if (sc == 2) pc = 0;
                if (!sc) {
                    cout << "NO" << endl;
                    goto e;
                }
                sc--;
                lc = i;
            }
        }
        cout << "YES" << endl;
        e:;
    }
}