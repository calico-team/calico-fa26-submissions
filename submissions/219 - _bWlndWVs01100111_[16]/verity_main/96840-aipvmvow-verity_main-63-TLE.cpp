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
        v<char> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }
        string guess = string(n, '_');
        int guess_idx = 0;
        while (guess != "CORRECT") {
            for (int i = 0; i < n; i++) {
                if (guess[i] == '_') {
                    guess[i] = a[guess_idx];
                }
            }
            cout << guess << flush << '\n';
            cin >> guess;
            guess_idx++;
        }
    }
    return 0;
}