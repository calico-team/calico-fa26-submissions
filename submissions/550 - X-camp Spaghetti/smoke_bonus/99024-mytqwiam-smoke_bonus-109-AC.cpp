
#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, R;
        cin >> N >> R;
        int available = 2;
        int pending = 0;
        long long nextTime = 0;
        bool ok = true;
        for (int i = 0; i < N; i++) {
            long long t;
            cin >> t;
            while (pending > 0 && nextTime <= t) {
                available++;
                pending--;
                nextTime += R;
            }
            if (available == 0) {
                ok = false;
                continue;
            }
            available--;
            if (pending == 0) {
                nextTime = t + R;
            }
            pending++;
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
    return 0;
}