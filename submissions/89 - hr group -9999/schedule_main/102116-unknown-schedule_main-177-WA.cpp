#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <set>
#include <unordered_set>
using namespace std;
typedef pair<int, int> pi;
typedef pair<string, string> ps;
typedef pair<pi, char> pic;
typedef pair<char, char> pc;
#define endl "\n"
#define int long long
const int MOD = 1e9 + 7;
const int HASH = 197;
const int MM = 1e4 + 10;
const int MV = 1;
int T, N, M, K, cnt;
int in[MM], vis[MM], dep[MM];
vector<int> graph[MM];
void dfs(int de, int maxdep, priority_queue<pi> pq, int maxK) {
    if (de > maxdep) return;
    queue<int> q;
    for (int i = 1; i <= maxK; i++) {
        if (!pq.empty()) {
            int u = pq.top().second; pq.pop(); cnt++;
            //cout<<i<<" "<<u<<" "<<cnt<<" "<<de<<endl;
            for (auto v : graph[u]) {
                vis[v] = vis[u] + 1;
                q.push(v);
            }
        }
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (dep[u] <= maxdep) {
            pq.push({dep[u], u});
        }
    }
    dfs(de + 1, maxdep, pq, maxK);
}
signed main() {
    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N >> M >> K;
        for (int i = 0; i < MM; i++) {
            graph[i].clear();
        }
        memset(vis, -1, sizeof(vis));
        memset(dep, 0, sizeof(dep));
        cnt = 0;
        priority_queue<pi> pq;
        queue<int> abc;
        for (int i = 1; i <= N; i++) {
            int x; cin >> x;
            if (x != 0) {
                graph[x].push_back(i); dep[x]++;
            } else {
                abc.push(i);
                vis[i] = 1;
            }
        }
        while (!abc.empty()) {
            int k = abc.front(); abc.pop();
            pq.push({dep[k], k});
        }
        dfs(1, M, pq, K);
        cout<<cnt<<endl;
    }
}