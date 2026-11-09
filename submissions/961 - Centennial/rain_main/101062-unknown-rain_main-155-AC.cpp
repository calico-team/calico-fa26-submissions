#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int x, y, z;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<Drone> dn, de;
        for (int i = 0; i < n; i++) {
            int x, y, z;
            char d;
            cin >> x >> y >> z >> d;
            if (d == 'N') dn.push_back({x, y, z});
            else de.push_back({x, y, z});
        }

        // sort by (x+y), then by x, so each group is sorted by x
        sort(de.begin(), de.end(), [](const Drone& a, const Drone& b) {
            int sa = a.x + a.y, sb = b.x + b.y;
            if (sa != sb) return sa < sb;
            return a.x < b.x;
        });

        long long out = (long long)n * k;

        for (const Drone& d : dn) {
            int s = d.x + d.y;

            auto lb = [&](int v) {
                return lower_bound(de.begin(), de.end(), make_pair(s, v),
                    [](const Drone& e, const pair<int,int>& key) {
                        int se = e.x + e.y;
                        if (se != key.first) return se < key.first;
                        return e.x < key.second;
                    });
            };

            auto pastIt  = lb(d.x);
            auto reachIt = lb(d.x - k + 1);

            out -= (pastIt - reachIt);
        }
        cout << out << '\n';
    }
}