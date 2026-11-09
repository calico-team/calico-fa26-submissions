#include <iostream>
#include <queue>

using namespace std;

void solve() {
    int N;
    long long R;
    if (!(cin >> N >> R)) return;
    
    int charges = 2;
    queue<long long> Q;
    bool ok = true;
    
    for (int i = 0; i < N; ++i) {
        long long t;
        cin >> t;

        while (!Q.empty() && Q.front() <= t) {
            Q.pop();
            charges++;
        }

        if (charges == 0) ok = false;
        else {
            charges--;
            Q.push(Q.empty() ? t + R : Q.back() + R);
        }
    }
    cout << (ok ? "YES\n" : "NO\n");
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (cin >> T) while (T--) solve();
}