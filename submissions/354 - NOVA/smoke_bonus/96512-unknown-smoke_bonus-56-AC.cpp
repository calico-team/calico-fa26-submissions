#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long r;
    cin >> n >> r;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cnt = 2;
    queue<long long> q;
    for (int i = 0; i < n; i++) {
        long long now = a[i];
        while (!q.empty() && q.front() <= now) {
            q.pop();
            cnt++;
        }
        if (cnt == 0) {
            cout << "NO"<<endl;
            return;
        }
        cnt--;
        long long finish = now + r;
        if (!q.empty()) {
            finish = q.back() + r;
        }
        q.push(finish);
    }

    cout << "YES"<<endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}

