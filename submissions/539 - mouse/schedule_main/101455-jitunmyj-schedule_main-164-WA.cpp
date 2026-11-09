#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        vector <vector <int>> res(n+1);
        for (int i = 0; i < n; i++) {
            int p;
            cin >> p;
            res[p].push_back(i+1);
        }
        priority_queue <pair <int, int>, vector <pair <int, int>>, greater <pair <int, int>>> q;
        int count = 0, sem = 1, ans = 0;
        for (const auto &i : res[0]) {
            q.push({1, i});
        }
        while (!q.empty()) {
            auto cur = q.top();
            q.pop();
            if (count >= k || sem < cur.first) {
                sem = max(sem+1, cur.first);
                count = 0;
            }
            if (sem > m) {
                break;
            }
            count++;
            ans++;
            for (auto &i : res[cur.second]) {
                q.push({sem+1, i});
            }
        }
        cout << ans << "\n";
    }
}