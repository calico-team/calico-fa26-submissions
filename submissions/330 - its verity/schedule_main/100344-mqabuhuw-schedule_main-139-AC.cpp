#include <bits/stdc++.h>

using namespace std;
#define sz(x) ((int)x.size())
typedef long long ll;
int n, m, k, p;
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    while (n --) {
        int num;
        cin >> m >> k >> p;
        deque<int> q;
        int dis[m + 1];
        vector<vector<int>> adj(m + 1);
        for (int i = 1; i <= m; i ++) {
            cin >> num;
            if (num == 0) {q.push_back(i); dis[i] = 0; }
            else {adj[num].push_back(i); dis[i] = 1e8; }
        }
        while (sz(q) > 0) {
            num = q.front(); q.pop_front();
            for (int i : adj[num]) {
                if (dis[i] == 1e8) {
                    q.push_back(i);
                    dis[i] = dis[num] + 1;
                }
            }
        }
        unordered_map<int, int> l;
        for (int i = 1; i <= m; i ++) {
            if (l.count(dis[i]) == 0) l[dis[i]] = 1;
            else l[dis[i]] ++;
        }
        int cur = 0; int ans = 0;
        for (int i = 0; i < k; i ++) {
            cur += l[i];
            if (cur >= p) {cur -= p; ans += p;}
            else {
                ans += cur;
                cur = 0;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
