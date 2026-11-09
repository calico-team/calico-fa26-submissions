#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;
    while (T--) {
        int n; long long r;
        cin >> n >> r;
        int ready = 2, pending = 0;
        long long nextReady = 0;
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            long long t; cin >> t;
            while (pending && nextReady <= t) {
                --pending;
                ++ready;
                nextReady += r;
            }
            if (ready == 0) ok = false;
            else {
                --ready;
                if (pending == 0) nextReady = t + r;
                ++pending;
            }
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
