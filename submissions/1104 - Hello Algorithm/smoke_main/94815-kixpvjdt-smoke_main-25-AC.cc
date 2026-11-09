#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--) {
        int N;
        long long R;
        cin >> N >> R;

        queue<long long> q;
        long long finish = 0;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long t;
            cin >> t;

            while (!q.empty() && q.front() <= t)
                q.pop();

            if (q.size() == 2) {
                possible = false;
                continue;
            }

            finish = max(finish, t) + R;
            q.push(finish);
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }

    return 0;
}
