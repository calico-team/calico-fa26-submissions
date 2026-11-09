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
    vector<vector<int>> adj(N);
    vector<int> indeg(N, 0);
    vector<int> height(N, 1);
    for (int i = 0; i < N; i++) {
        if (P[i] != 0) {
            int par = P[i] - 1;
            adj[par].push_back(i);
            indeg[i]++;
        }
    }
    vector<int> order;
    order.reserve(N);
    vector<int> q;
    for (int i = 0; i < N; i++) {
        if (indeg[i] == 0)
            q.push_back(i);
    }
    for (int i = 0; i < (int)q.size(); i++) {
        int u = q[i];
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0)
                q.push_back(v);
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        int u = order[i];
        for (int v : adj[u]) {
            height[u] = max(height[u], height[v] + 1);
        }
    }
    priority_queue<pair<int, int>> pq;
    for (int i = 0; i < N; i++) {
        if (P[i] == 0) {
            pq.push({height[i], i});
        }
    }
    int ans = 0;
    for (int semester = 0; semester < M; semester++) {
        vector<int> completed;
        int take = min(K, (int)pq.size());
        for (int j = 0; j < take; j++) {
            int u = pq.top().second;
            pq.pop();
            completed.push_back(u);
            ans++;
        }
        for (int u : completed) {
            for (int v : adj[u]) {
                pq.push({height[v], v});
            }
        }
        if (pq.empty())
            break;
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