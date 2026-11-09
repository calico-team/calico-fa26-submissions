#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ull = unsigned long long;
vector<string> grid;
int n, m;

vector<int> parent, r;
void make_set(int v) {
    parent[v] = v;
    r[v] = 1;
}

int find_set(int v) {
    if (v == parent[v])
        return v;
    parent[v] = find_set(parent[v]);
    return parent[v];
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    if (a != b) {
        if (r[a] < r[b])
            swap(a, b);
        parent[b] = a;
        r[a] += r[b];
    }
}

int get_node(int r, int c, char ch) {
    return 2 * (r * m + c) + (ch == 'B');
}

void update(int r, int c, char mode) {
    static const int dr[2] = {0, 1};
    static const int dc[2] = {1, 0};
    for (int d = 0; d < 2; d++) {
        int row = r + dr[d];
        int col = c + dc[d];
        if (row >= n || col >= m) continue;
        if (grid[row][col] == mode || grid[row][col] == '.' || grid[r][c] == '.') {
            union_sets(get_node(row, col, grid[row][col]), get_node(r, c, grid[r][c]));
        }
    }
}

void solve() {
    int q;
    cin >> n >> m >> q;
    grid.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    parent.resize(2 * m * n, 0);
    r.resize(2 * m * n, 0);
    for (int i = 0; i < 2 * m * n; i++) {
        make_set(i);
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '.')
                union_sets(get_node(r, c, 'A'), get_node(r, c, 'B'));
            update(r, c, grid[r][c]);
        }
    }

    for (int i = 0; i < q; i++) {
        int rs, cs, re, ce;
        cin >> rs >> cs >> re >> ce;
        cout << ((find_set(get_node(rs, cs, 'B')) == find_set(get_node(re, ce, 'A')) || find_set(get_node(rs, cs, 'B')) == find_set(get_node(re, ce, 'B'))) ? "YES\n" : "NO\n");
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}