#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
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
    vector<int> order, h(N + 1, 1);
    for (int i = 1; i <= N; i++) ch[P[i - 1]].push_back(i);
    // BFS from virtual root 0 gives parents before children
    order.push_back(0);
    for (size_t i = 0; i < order.size(); i++)
        for (int c : ch[order[i]]) order.push_back(c);
    for (int i = (int)order.size() - 1; i >= 1; i--) {
        int u = order[i];
        for (int c : ch[u]) h[u] = max(h[u], h[c] + 1);
    }
    // Highest-level-first greedy
    priority_queue<pair<int,int>> pq;
    for (int c : ch[0]) pq.push({h[c], c});
    int taken = 0;
    for (int s = 0; s < M && !pq.empty(); s++) {
        vector<int> now;
        for (int k = 0; k < K && !pq.empty(); k++) {
            now.push_back(pq.top().second);
            pq.pop();
        }
        taken += now.size();
        for (int u : now) for (int c : ch[u]) pq.push({h[c], c});
    }
    return taken;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--){
        int N, M, K; cin >> N >> M >> K;
        vector<int> P(N);
        for (int i = 0; i < N; i++) cin >> P[i];
        cout << solve(N, M, K, P) << "\n";
    }
}
