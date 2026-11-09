#include <iostream>

using namespace std;

void solve() {
    int n;
    long long r;
    if (!(cin >> n >> r)) return;

    // r1 and r2 track completion timestamps of up to 2 sequential recharges (0 = inactive)
    long long r1 = 0, r2 = 0;
    bool possible = true;

    for (int i = 0; i < n; ++i) {
        long long t;
        cin >> t;
        if (!possible) continue;

        if (r1 <= t) {
            if (r2 <= t) {
                r1 = t + r;
                r2 = 0;
            } else {
                r1 = r2;
                r2 = r2 + r;
            }
        } else {
            if (r2 == 0) {
                r2 = r1 + r;
            } else {
                possible = false;
            }
        }
    }

    cout << (possible ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
