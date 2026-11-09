#pragma GCC optimize("O3")
#include "bits/stdc++.h"
#define debug(x) cout << #x << " is " << x << endl;
using namespace std;
#define int long long
#define pii pair<int, int>
template<typename T> using min_pq = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using vv = vector<vector<T>>;
template<typename T> using v = vector<T>;
#define fb(x) x.begin(), x.end()
#define lsb(x) (x & -x)

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int total = n*k;
        v<int> xn, xe, yn, ye;
        for (int i = 0; i < n; i++) {
            int a, b, c;
            char d;
            cin >> a >> b >> c >> d;
            if (d == 'N') {
                xn.push_back(a);
                yn.push_back(b);
            } else {
                xe.push_back(a);
                ye.push_back(b);
            }
        }
        for (int i = 0; i < xn.size(); i++) {
            for (int j = 0; j < xe.size(); j++) {
                if (xn[i] - xe[j] > 0 && xn[i]-xe[j] == ye[j]-yn[i] && xn[i]-xe[j] <= k-1) {
                    total--;
                }
            }
        }
        cout << total << '\n';
    }
    return 0;
}
