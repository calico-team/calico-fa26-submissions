#include <bits/stdc++.h>
using namespace std;

/*
* Return an integer denoting the amount of rain collected after the Kth nights
* 
* N: Number of drones
* K: Number of nights
* L: a list in this order [X, Y, Z, D] for each drone
*   X: Starting X location of Drone
*   Y: Starting Y location of Drone
*   Z: Starting Z location of Drone
*   D: Starting direction of Drone
*/

// Count pairs (i in Q, j in T) with same x+y, z_j > z_i and x_j - x_i in [lo(i), hi(i)].
// dirSign = +1: partner is to the east side (x_j > x_i), -1: partner is to the west.
static long long countBlocked(const vector<array<long long,3>>& Q, const vector<array<long long,3>>& T,
                              int K, int dirSign) {
    const long long M = 100001;
    // key = s*M + x ; arrays hold {z, x, s}
    vector<long long> keys;
    for (auto& t : T) keys.push_back(t[2] * M + t[1]);
    sort(keys.begin(), keys.end());
    int m = keys.size();
    vector<int> bit(m + 1, 0);
    auto add = [&](int i) { for (i++; i <= m; i += i & -i) bit[i]++; };
    auto pre = [&](int i) { int r = 0; for (; i > 0; i -= i & -i) r += bit[i]; return r; }; // first i entries
    // events: z descending; queries before inserts at equal z
    vector<tuple<long long,int,int>> ev; // (z, type 0=query 1=insert, idx)
    for (int i = 0; i < (int)Q.size(); i++) ev.push_back({Q[i][0], 0, i});
    for (int i = 0; i < (int)T.size(); i++) ev.push_back({T[i][0], 1, i});
    sort(ev.begin(), ev.end(), [](auto& a, auto& b) {
        if (get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
        return get<1>(a) < get<1>(b);
    });
    long long total = 0;
    for (auto& [z, type, idx] : ev) {
        if (type == 1) {
            long long key = T[idx][2] * M + T[idx][1];
            add(lower_bound(keys.begin(), keys.end(), key) - keys.begin());
        } else {
            long long x = Q[idx][1], s = Q[idx][2];
            long long lx, hx;
            if (dirSign > 0) { lx = x + 1; hx = min<long long>(x + K - 1, 100000); }
            else { lx = max<long long>(x - K + 1, 0); hx = x - 1; }
            if (lx > hx) continue;
            long long lk = s * M + lx, hk = s * M + hx;
            int l = lower_bound(keys.begin(), keys.end(), lk) - keys.begin();
            int r = upper_bound(keys.begin(), keys.end(), hk) - keys.begin();
            total += pre(r) - pre(l);
        }
    }
    return total;
}

long long solve(int N, int K, vector<tuple<int, int, int, char>> L){
    // Two drones can only ever be stacked if one moves E and the other N, on the same
    // anti-diagonal x+y, meeting at exactly one night. Each such (lower, higher) pair
    // costs the lower drone one unit of rain, and no two pairs share a night for a drone.
    vector<array<long long,3>> E, Nn; // {z, x, s}
    for (auto& [x, y, z, d] : L) {
        array<long long,3> a = {z, x, x + y};
        (d == 'E' ? E : Nn).push_back(a);
    }
    long long blocked = countBlocked(E, Nn, K, +1)   // E drone below, N drone to its east
                      + countBlocked(Nn, E, K, -1);  // N drone below, E drone to its west
    return (long long)N * K - blocked;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t; cin>>t;
    while (t--){
        int N, K; cin>>N>>K;
        vector<tuple<int, int, int, char>> L;
        for (int i = 0; i < N; i++){
            int X, Y, Z;
            char D;
            cin>>X>>Y>>Z>>D;
            L.push_back({X, Y, Z, D});
        }
        cout<<solve(N, K, L)<<endl;
    }
}
