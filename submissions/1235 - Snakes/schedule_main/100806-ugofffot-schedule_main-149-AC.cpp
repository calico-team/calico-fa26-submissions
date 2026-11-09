#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

/** 
 * Return the maximum number of classes that can be taken across M semesters.
 *    
 * N: the number of classes
 * M: the number of semesters
 * K: the maximum number of classes you can take per semester
 * P: a prerequisite array for classes 1 to N (0 if there are no prerequisite classes)
 */
int solve(int N, int M, int K, vector<int> &P){
    vector<vector<int>> ch(N + 1);
    for (int i = 1; i <= N; i++) ch[P[i - 1]].push_back(i);
    vector<int> h(N + 1);
    function<int(int)> dfs = [&](int u) {
        for (int v : ch[u]) h[u] = max(h[u], dfs(v));
        return ++h[u];
    };
    dfs(0);
    priority_queue<pair<int, int>> pq;
    for (int v : ch[0]) pq.push({h[v], v});
    int ans = 0;
    for (int s = 0; s < M && !pq.empty(); s++) {
        vector<int> took;
        while (!pq.empty() && (int)took.size() < K) took.push_back(pq.top().second), pq.pop();
        ans += took.size();
        for (int u : took) for (int v : ch[u]) pq.push({h[v], v});
    }
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
        cout << solve(N, M, K, P) << '\n';
    }
}