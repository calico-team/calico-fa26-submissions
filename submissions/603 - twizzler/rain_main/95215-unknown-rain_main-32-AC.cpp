#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        map<int, pair<vector<int>, vector<int>>> g;
        for (int i = 0; i < n; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if (d == 'E') {
                g[x + y].first.push_back(x);
            } else {
                g[x + y].second.push_back(x);
            }
        }

        long long lost = 0;
        for (auto &entry : g) {
            vector<int> &e = entry.second.first;
            vector<int> &nn = entry.second.second;
            sort(nn.begin(), nn.end());

            for (int x : e) {
                auto lo = lower_bound(nn.begin(), nn.end(), (long long)x);
                auto hi = upper_bound(nn.begin(), nn.end(), (long long)x + k - 1);
                lost += hi - lo;
            }
        }

        cout << (long long)n * k - lost << "\n";
    }
}
