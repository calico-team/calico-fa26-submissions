#include <iostream>
#include <vector>
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
    vector<int> depth(N + 1, 0);
    auto get_depth = [&](auto& self, int u) -> int {
        if (u == 0) return 0;
        if (depth[u] != 0) return depth[u];
        if (P[u - 1] == 0) return depth[u] = 1;
        return depth[u] = self(self, P[u - 1]) + 1;
    };

    for (int i = 1; i <= N; i++) {
        get_depth(get_depth, i);
    }

    vector<int> cnt(N + 2, 0);
    for (int i = 1; i <= N; i++) {
        cnt[depth[i]]++;
    }

    long long available = 0;
    long long taken = 0;
    for (int s = 1; s <= M; s++) {
        available += cnt[s];
        long long can_take = min((long long)K, available - taken);
        taken += can_take;
    }

    return (int)taken;
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