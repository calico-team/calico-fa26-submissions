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

    for (int i = 1; i <= N; i++) {
        if (depth[i] != 0) continue;
        
        vector<int> path;
        int curr = i;
        while (curr != 0 && depth[curr] == 0) {
            path.push_back(curr);
            curr = P[curr - 1];
        }
        
        int base_depth = (curr == 0) ? 0 : depth[curr];
        for (int j = (int)path.size() - 1; j >= 0; j--) {
            base_depth++;
            depth[path[j]] = base_depth;
        }
    }

    vector<int> cnt(N + 2, 0);
    for (int i = 1; i <= N; i++) {
        if (depth[i] < (int)cnt.size()) {
            cnt[depth[i]]++;
        }
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