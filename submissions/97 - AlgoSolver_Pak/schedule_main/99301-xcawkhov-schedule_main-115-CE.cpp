#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        vector<int> p(N + 1);
        for (int i = 1; i <= N; i++) cin >> p[i];

        vector<int> depth(N + 1, 0);
        for (int i = 1; i <= N; i++) {
            if (p[i] == 0) depth[i] = 1;
            else depth[i] = depth[p[i]] + 1;
        }

        vector<int> order;
        for (int i = 1; i <= N; i++) order.push_back(i);
        sort(order.begin(), order.end(), [&](int a, int b) {
            return depth[a] < depth[b];
        });

        vector<int> cnt(M + 2, 0);
        vector<int> sem(N + 1, 0);
        int ans = 0;

        for (int id : order) {
            int s = depth[id];
            if (p[id] != 0) s = max(s, sem[p[id]] + 1);
            while (s <= M && cnt[s] >= K) s++;
            if (s > M) continue;
            sem[id] = s;
            cnt[s]++;
            ans++;
        }
        cout << ans << "\n";
    }
    return 0;
}