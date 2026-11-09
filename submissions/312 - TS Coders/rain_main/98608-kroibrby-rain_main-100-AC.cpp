#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

struct Drone { int x, y, z; char d; };
struct Fenwick {
    int n; vector<int> bit;
    Fenwick(int n = 0): n(n), bit(n + 1, 0) {}
    void add(int i, int v) { for (; i <= n; i += i & -i) bit[i] += v; }
    int sum(int i) const { int s = 0; for (; i > 0; i -= i & -i) s += bit[i]; return s; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int n; int64 K; cin >> n >> K;
        unordered_map<int, vector<Drone>> groups;
        groups.reserve(n * 2);
        for (int i = 0; i < n; ++i) {
            Drone a; cin >> a.x >> a.y >> a.z >> a.d;
            groups[a.x + a.y].push_back(a);
        }
        int64 blocked = 0;
        for (auto &entry : groups) {
            vector<Drone> east, north;
            for (auto &a : entry.second) (a.d == 'E' ? east : north).push_back(a);
            if (east.empty() || north.empty()) continue;
            sort(east.begin(), east.end(), [](const Drone& a, const Drone& b){ return a.x < b.x; });
            sort(north.begin(), north.end(), [](const Drone& a, const Drone& b){ return a.x < b.x; });
            vector<int> zs;
            for (auto &a : east) zs.push_back(a.z);
            sort(zs.begin(), zs.end()); zs.erase(unique(zs.begin(), zs.end()), zs.end());
            Fenwick fw((int)zs.size());
            int left = 0, right = 0, active = 0;
            for (const auto &b : north) {
                while (right < (int)east.size() && east[right].x <= b.x) {
                    int p = lower_bound(zs.begin(), zs.end(), east[right].z) - zs.begin() + 1;
                    fw.add(p, 1); ++active; ++right;
                }
                int64 minX = (int64)b.x - (K - 1);
                while (left < right && east[left].x < minX) {
                    int p = lower_bound(zs.begin(), zs.end(), east[left].z) - zs.begin() + 1;
                    fw.add(p, -1); --active; ++left;
                }
                int p = lower_bound(zs.begin(), zs.end(), b.z) - zs.begin();
                int lower = fw.sum(p);
                int atMost = fw.sum((int)(upper_bound(zs.begin(), zs.end(), b.z) - zs.begin()));
                int higher = active - atMost;
                blocked += lower + higher;
            }
        }
        cout << (int64)n * K - blocked << '\n';
    }
}
