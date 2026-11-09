#include <bits/stdc++.h>
using namespace std;
struct Query {
    int start, blue_end, red_end, left_col, right_col, limit;
};
class GridQueries {
    static constexpr int infinity = 1'000'000'000;
    int stride;
    vector<array<int, 5>> neighbors;
    vector<int> degree, distance, seen, bfs_queue;
    vector<Query> queries;
    vector<bool> possible;
    int stamp = 0;

    void connect(int a, int b) {
        neighbors[a][degree[a]++] = b;
        neighbors[b][degree[b]++] = a;
    }
    int get_distance(int vertex) const {
        return vertex >= 0 && seen[vertex] == stamp ? distance[vertex] : infinity;
    }
    void bfs(int source, int first, int end) {
        ++stamp;
        int tail = 0;
        bfs_queue[tail++] = source;
        seen[source] = stamp;
        distance[source] = 0;
        for (int head = 0; head < tail; ++head) {
            int vertex = bfs_queue[head];
            for (int i = 0; i < degree[vertex]; ++i) {
                int next = neighbors[vertex][i];
                if (next < first || next >= end || seen[next] == stamp) continue;
                seen[next] = stamp;
                distance[next] = distance[vertex] + 1;
                bfs_queue[tail++] = next;
            }
        }
    }

    void divide(int left, int right, const vector<int> &pending) {
        if (pending.empty()) return;
        int middle = (left + right) / 2;
        for (int source = middle * stride; source < (middle + 1) * stride; ++source) {
            if (!degree[source]) continue;
            bfs(source, left * stride, (right + 1) * stride);
            for (int index : pending) {
                if (possible[index]) continue;
                const auto &query = queries[index];
                int to_end = min(get_distance(query.blue_end), get_distance(query.red_end));
                int from_start = get_distance(query.start);
                if (from_start != infinity && to_end != infinity &&
                    from_start + to_end <= query.limit) possible[index] = true;
            }
        }
        vector<int> before, after;
        for (int index : pending) {
            if (possible[index]) continue;
            const auto &query = queries[index];
            if (query.right_col < middle) before.push_back(index);
            else if (query.left_col > middle) after.push_back(index);
        }
        if (!before.empty()) divide(left, middle - 1, before);
        if (!after.empty()) divide(middle + 1, right, after);
    }

public:
    GridQueries(int n, int m, int q)
        : stride(2 * n), neighbors(stride * m), degree(stride * m),
          distance(stride * m), seen(stride * m), bfs_queue(stride * m),
          queries(q), possible(q) {
        vector<string> grid(n);
        for (auto &row : grid) cin >> row;
        auto id = [&](int r, int c, int mode) { return c * stride + 2 * r + mode; };
        auto active = [&](int r, int c, int mode) {
            return grid[r][c] == '.' || grid[r][c] == "BR"[mode];
        };
        for (int c = 0; c < m; ++c) {
            for (int r = 0; r < n; ++r) {
                if (grid[r][c] == '.') connect(id(r, c, 0), id(r, c, 1));
                for (int mode = 0; mode < 2; ++mode) {
                    if (!active(r, c, mode)) continue;
                    if (r && active(r - 1, c, mode)) connect(id(r, c, mode), id(r - 1, c, mode));
                    if (c && active(r, c - 1, mode)) connect(id(r, c, mode), id(r, c - 1, mode));
                }
            }
        }
        vector<int> pending;
        for (int i = 0; i < q; ++i) {
            int sr, sc, er, ec, limit;
            cin >> sr >> sc >> er >> ec >> limit;
            queries[i] = {id(sr, sc, 0), active(er, ec, 0) ? id(er, ec, 0) : -1,
                          active(er, ec, 1) ? id(er, ec, 1) : -1,
                          min(sc, ec), max(sc, ec), limit};
            if (sr == er && sc == ec) possible[i] = true;
            else if (abs(sr - er) + abs(sc - ec) <= limit) pending.push_back(i);
        }
        divide(0, m - 1, pending);
        for (bool answer : possible) cout << (answer ? "YES\n" : "NO\n");
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, m, q;
        cin >> n >> m >> q;
        GridQueries solver(n, m, q);
    }
}
