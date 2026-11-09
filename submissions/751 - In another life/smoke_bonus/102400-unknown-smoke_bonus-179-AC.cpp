#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n, r, last = 0;
    cin >> n >> r;
    vector<long long> a(n);
    for (long long &x : a) cin >> x;

    queue<long long> q;
    for (long long x : a) {
        while (!q.empty() && q.front() <= x) q.pop();
        if (q.size() >= 2) {
            cout << "NO\n";
            return;
        }
        last = max(x, last) + r;
        q.push(last);
    }
    cout << "YES\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
