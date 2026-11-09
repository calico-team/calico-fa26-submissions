#include <bits/stdc++.h>
using namespace std;

#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL);

int main() {
    FAST_IO
    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;

        vector<int> p(n + 1), cnt(n + 1, 0), h(n + 1, 1);
        vector<vector<int>> children(n + 1);

        for (int i = 1; i <= n; i++) {
            cin >> p[i];
            if (p[i] != 0) {
                children[p[i]].push_back(i);
                cnt[p[i]]++;
            }
        }

        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (cnt[i] == 0) q.push(i);
        }

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            if (p[x] != 0) {
                int y = p[x];
                h[y] = max(h[y], h[x] + 1);
                cnt[y]--;
                if (cnt[y] == 0) q.push(y);
            }
        }

        priority_queue<pair<int, int>> available;
        for (int i = 1; i <= n; i++) {
            if (p[i] == 0)
                available.push({h[i], i});
        }

        int ans = 0;
        for (int semester = 0; semester < m && !available.empty(); semester++) {
            int take = min(k, (int)available.size());
            vector<int> unlocked;

            for (int j = 0; j < take; j++) {
                int x = available.top().second;
                available.pop();
                ans++;

                for (int y : children[x])
                    unlocked.push_back(y);
            }

            for (int x : unlocked)
                available.push({h[x], x});
        }

        cout << ans << "\n";
    }

    return 0;
}
