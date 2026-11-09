#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, r; cin >> n >> r;
        vector<int> vec; vec.resize(n);
        for (int i = 0; i < n; i++) cin >> vec[i];

        bool res = true;
        int charge = r;
        for (int i = 1; i < n; i++) {
            int t = vec[i] - vec[i-1];
            charge = min(charge + t, r * 2);
            if (charge < r) {
                res = false;
                break;
            }
            charge -= r;
        }

        cout << (res ? "YES" : "NO") << endl;
    }
    return 0;
}