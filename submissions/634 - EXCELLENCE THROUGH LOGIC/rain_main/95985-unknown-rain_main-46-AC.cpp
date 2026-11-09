
#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int x, y, z;
    char dir;
};

struct BIT {
    int n;
    vector<int> tree;

    BIT(int n) : n(n), tree(n + 1, 0) {}

    void update(int i) {
        for (; i <= n; i += i & -i) {
            tree[i]++;
        }
    }

    int query(int i) {
        int result = 0;

        for (; i > 0; i -= i & -i) {
            result += tree[i];
        }

        return result;
    }

    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

void solve() {
    int n;
    long long k;
    cin >> n >> k;

    vector<vector<Drone>> groups(200001);

    for (int i = 0; i < n; i++) {
        int x, y, z;
        char dir;
        cin >> x >> y >> z >> dir;

        groups[x + y].push_back({x, y, z, dir});
    }

    long long blocked = 0;

    for (auto &g : groups) {
        if (g.empty()) continue;

        vector<int> coords;

        for (auto &d : g) {
            coords.push_back(d.x);
        }

        sort(coords.begin(), coords.end());
        coords.erase(unique(coords.begin(), coords.end()), coords.end());

        sort(g.begin(), g.end(), [](const Drone &a, const Drone &b) {
            return a.z > b.z;
        });

        BIT east((int)coords.size());
        BIT north((int)coords.size());

        for (int i = 0; i < (int)g.size();) {
            int j = i;

            while (j < (int)g.size() && g[j].z == g[i].z) {
                j++;
            }

            for (int p = i; p < j; p++) {
                int x = g[p].x;

                if (g[p].dir == 'E') {
                    int l = lower_bound(coords.begin(), coords.end(), x)
                            - coords.begin() + 1;

                    int r = upper_bound(coords.begin(), coords.end(),
                                        x + k - 1)
                            - coords.begin();

                    blocked += north.rangeQuery(l, r);
                } else {
                    int l = lower_bound(coords.begin(), coords.end(),
                                        x - k + 1)
                            - coords.begin() + 1;

                    int r = upper_bound(coords.begin(), coords.end(), x)
                            - coords.begin();

                    blocked += east.rangeQuery(l, r);
                }
            }

            for (int p = i; p < j; p++) {
                int pos = lower_bound(coords.begin(), coords.end(), g[p].x)
                          - coords.begin() + 1;

                if (g[p].dir == 'E') {
                    east.update(pos);
                } else {
                    north.update(pos);
                }
            }

            i = j;
        }
    }

    cout << 1LL * n * k - blocked << '\n';
}

void read_your_input() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_your_input();

    return 0;
}
