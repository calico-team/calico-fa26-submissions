#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int K, vector<tuple<int, int, int, char>> L) {
    long long total = (long long)N * K;
    unordered_map<int, vector<int>> east_drones;
    unordered_map<int, vector<int>> north_drones;

    for (int i = 0; i < N; i++) {
        int X = get<0>(L[i]);
        int Y = get<1>(L[i]);
        char D = get<3>(L[i]);
        int sum = X + Y;
        if (D == 'E') east_drones[sum].push_back(X);
        else north_drones[sum].push_back(X);
    }

    long long blocked = 0;
    for (auto& [sum, e_list] : east_drones) {
        if (!north_drones.count(sum)) continue;
        auto& n_list = north_drones[sum];
        sort(n_list.begin(), n_list.end());

        for (int xe : e_list) {
            auto it1 = lower_bound(n_list.begin(), n_list.end(), xe);
            auto it2 = lower_bound(n_list.begin(), n_list.end(), (long long)xe + K);
            blocked += (it2 - it1);
        }
    }
    return total - blocked;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; if (!(cin >> t)) return 0;
    while (t--) {
        int N, K; cin >> N >> K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++) {
            int X, Y, Z; char D;
            cin >> X >> Y >> Z >> D;
            L.push_back({X, Y, Z, D});
        }
        cout << solve(N, K, L) << "\n";
    }
}