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
        queue <int> q;
        for (const auto &i : res[0]) {
            q.push(i);
        }
        int ans = 0;
        for (int i = 0; i < m; i++) {
            if (q.empty()) {
                break;
            }
            vector <int> next;
            for (int j = 0; j < k && !q.empty(); j++) {
                for (const auto &l : res[q.front()]) {
                    next.push_back(l);
                }
                q.pop();
                ans++;
            }
            for (const auto &j : next) {
                q.push(j);
            }
        }
        cout << ans << "\n";
    }
}