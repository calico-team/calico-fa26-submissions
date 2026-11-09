#include<bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) x.begin(), x.end()
#define rep(i, a, b) for (int i = a; i < b; i++)
#define rrep(i, a, b) for (int i = a; i >= b; i--)
#define vi vector<int>
#define si set<int>
#define vvi vector<vector<int>>
#define pii pair<int, int>
#define vpii vector<pair<int, int>>

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n, r;
        cin >> n >> r;
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        int charge1 = 0, charge2 = 0;
        bool gud = 1;
        rep(i, 0, n) {
            if (!charge1) {
                charge1 = r;
            }
            else {
                if (!charge2) {
                    charge2 = r;
                }
                else {
                    gud = 0;
                }
            }
            if (i != n - 1) {
                int diff = a[i + 1] - a[i];
                if (diff <= charge1)
                    charge1 -= diff;
                else
                    charge2 -= diff-charge1, charge1 = 0, charge2 = max(0ll, charge2), swap(charge1, charge2);
            }
        }
        cout << (gud ? "YES" : "NO") << endl;
    }
}
