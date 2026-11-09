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
        vector <int> sem(n+1, -1);
        queue <pair <int, int>> q;
        int count = 0, s = 1, ans = 0;
        for (const auto &i : res[0]) {
            q.push({i, 1});
        }
        while (!q.empty()) {
            auto cur = q.front();
            q.pop();
            if (count == k || s < cur.second) {
                s = max(s+1, cur.second);
                ans += count;
                count = 0;
            }
            if (s > m) {
                break;
            }
            count++;
            for (auto &i : res[cur.first]) {
                q.push({i, s+1});
            }
        }
        ans += count;
        cout << ans << "\n";
    }
}