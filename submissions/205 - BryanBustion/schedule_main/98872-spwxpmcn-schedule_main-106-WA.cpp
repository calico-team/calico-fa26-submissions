#include <bits/stdc++.h>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */
int solve(int N, int M, int K, vector<int> &P) {
    vector<vector<int>> adj(N + 1);
    vector<int> parent(N + 1);
    vector<int> height(N + 1, 1);
    vector<int> childCount(N + 1, 0);
    for (int i = 1; i <= N; i++) {
        parent[i] = P[i - 1];
        if (parent[i] != 0) {
            adj[parent[i]].push_back(i);
            childCount[parent[i]]++;
        }
    }
    queue<int> q;
    vector<int> remaining = childCount;
    for (int i = 1; i <= N; i++) {
        if (remaining[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        int p = parent[u];
        if (p != 0) {
            height[p] = max(height[p], height[u] + 1);
            remaining[p]--;
            if (remaining[p] == 0) {
                q.push(p);
            }
        }
    }
    priority_queue<tuple<int, int, int>> pq;
    for (int i = 1; i <= N; i++) {
        if (parent[i] == 0) {
            pq.push({(int)adj[i].size(), height[i], i});
        }
    }
    int ans = 0;
    for (int semester = 1; semester <= M && !pq.empty(); semester++) {
        vector<tuple<int, int, int>> next;
        for (int j = 0; j < K && !pq.empty(); j++) {
            auto [children, h, u] = pq.top();
            pq.pop();
            ans++;
            for (int v : adj[u]) {
                next.push_back({
                    (int)adj[v].size(),
                    height[v],
                    v
                });
            }
        }
        for (auto &item : next) {
            pq.push(item);
        }
    }
    cout << ans << '\n';
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        solve(N, M, K, P);
    }
}