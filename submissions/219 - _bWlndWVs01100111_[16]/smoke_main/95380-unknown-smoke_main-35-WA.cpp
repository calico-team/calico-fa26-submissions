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
        int n, r;
        cin >> n >> r;
        v<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int last = a[0];
        int cooldown_to_2 = 0;
        bool fail = false;
        for (int num: a) {
            cooldown_to_2 += r;
            cooldown_to_2 -= num - last;
            if (cooldown_to_2 > r*2) {
                fail = true;
                break;
            }
            last = num;
        }
        if (fail) {
            cout << "NO" << '\n';
        } else {
            cout << "YES" << '\n';
        }
    }
    return 0;
}