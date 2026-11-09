#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int N, int M, int K, vector<int> &P){
    vector<vector<int>> children(N + 1);
    vector<int> in_degree(N + 1, 0);

    for (int i = 0; i < N; ++i) {
        int u = P[i];
        int v = i + 1;
        if (u != 0) {
            children[u].push_back(v);
            in_degree[v]++;
        }
    }

    vector<int> q;
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            q.push_back(i);
        }
    }

    vector<int> depth(N + 1, 1);
    int max_depth = 1;

    int head = 0;
    while (head < (int)q.size()) {
        int u = q[head++];
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            max_depth = max(max_depth, depth[v]);
            q.push_back(v);
        }
    }

    vector<int> count_at_depth(max_depth + 1, 0);
    for (int i = 1; i <= N; ++i) {
        count_at_depth[depth[i]]++;
    }

    long long total_courses = 0;
    long long carry = 0;

    for (int sem = 1; sem <= M; ++sem) {
        long long available = carry;
        if (sem <= max_depth) {
            available += count_at_depth[sem];
        }

        long long taken = min((long long)K, available);
        total_courses += taken;
        carry = available - taken;
    }

    cout << total_courses << "\n";
    return total_courses;
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