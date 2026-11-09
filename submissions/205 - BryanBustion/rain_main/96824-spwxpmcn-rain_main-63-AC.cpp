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


long long solve(int N, int K, vector<tuple<int, int, int, char>> L) {
    struct Point {
        int coord, z, idx;
    };
    struct Query {
        int l, r, z, id;
    };
    struct Fenwick {
        int n;
        vector<int> bit;
        Fenwick(int n) : n(n), bit(n + 1, 0) {}
        void update(int i) {
            for (; i <= n; i += i & -i)
                bit[i]++;
        }
        int query(int i) {
            int res = 0;
            for (; i > 0; i -= i & -i)
                res += bit[i];
            return res;
        }
        int rangeQuery(int l, int r) {
            return query(r) - query(l);
        }
    };
    map<int, vector<Point>> east, north;
    vector<tuple<int, int, int, char>> drones = L;
    for (int i = 0; i < N; i++) {
        auto [x, y, z, d] = drones[i];
        if (d == 'E')
            east[x + y].push_back({y, z, 0});
        else
            north[x + y].push_back({x, z, 0});
    }
    for (auto &[d, v] : east)
        sort(v.begin(), v.end(),
             [](const Point &a, const Point &b) {
                 return a.coord < b.coord;
             });
    for (auto &[d, v] : north)
        sort(v.begin(), v.end(),
             [](const Point &a, const Point &b) {
                 return a.coord < b.coord;
             });
    int total = 0;
    vector<pair<int, int>> points;
    for (auto &[d, v] : east) {
        for (auto &p : v) {
            p.idx = ++total;
            points.push_back({p.z, p.idx});
        }
    }
    for (auto &[d, v] : north) {
        for (auto &p : v) {
            p.idx = ++total;
            points.push_back({p.z, p.idx});
        }
    }
    vector<Query> queries;
    for (int i = 0; i < N; i++) {
        auto [x, y, z, dir] = drones[i];
        int diagonal = x + y;
        vector<Point> *v = nullptr;
        if (dir == 'E') {
            auto it = north.find(diagonal);
            if (it == north.end())
                continue;
            v = &it->second;
        }
        else {
            auto it = east.find(diagonal);
            if (it == east.end())
                continue;
            v = &it->second;
        }
        int coord = (dir == 'E') ? x : y;
        int l = lower_bound(
            v->begin(), v->end(), coord,
            [](const Point &p, int val) {
                return p.coord < val;
            }
        ) - v->begin();
        int r = lower_bound(
            v->begin(), v->end(), coord + K,
            [](const Point &p, int val) {
                return p.coord < val;
            }
        ) - v->begin();
        if (l == r)
            continue;
        int base = (*v)[0].idx;
        queries.push_back({
            base + l - 1,
            base + r - 1,
            z,
            i
        });
    }
    sort(points.begin(), points.end(),
         [](const auto &a, const auto &b) {
             return a.first > b.first;
         });
    sort(queries.begin(), queries.end(),
         [](const Query &a, const Query &b) {
             return a.z > b.z;
         });
    Fenwick bit(total);
    vector<long long> blocked(N, 0);
    int ptr = 0;
    for (const auto &q : queries) {
        while (ptr < (int)points.size() &&
               points[ptr].first > q.z) {
            bit.update(points[ptr].second);
            ptr++;
        }
        blocked[q.id] = bit.rangeQuery(q.l, q.r);
    }
    long long answer = 1LL * N * K;
    for (int i = 0; i < N; i++)
        answer -= blocked[i];
    return answer;
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