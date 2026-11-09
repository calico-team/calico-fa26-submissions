#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<ll, ll> pll;

/** for blitz */
// ifstream cin("input.txt");
// ofstream cout("output.txt");

/** DSU */

vi p;
vi s;

void make_set(int v) {
    p[v] = v;
    s[v] = 1;
}

int find_set(int v) {
    if (v == -1) return -1;
    while (p[v] != v) v = p[v];
    return v;
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);

    if (a != b) {
        if (s[a] < s[b]) {
            swap(a, b);
        }
        p[b] = a;
        s[a] += s[b];
    }
}

void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<string> grid(n);
    rep(i, 0, n) cin >> grid[i];

    /** preprocessing */

    p.assign(n*m, 0);
    s.assign(n*m, 0);
    rep(i, 0, n*m) make_set(i);

    queue<pii> qu;
    vector<vi> visited(n, vi(m, -1));
    rep(i, 0, n) {
        rep(j, 0, m) {
            if (grid[i][j] == '.') {
                visited[i][j] = (i*m) + j;
                qu.push({i, j});
            }
        }
    }

    while(!qu.empty()) {
        int x = qu.front().first;
        int y = qu.front().second;
        qu.pop();

        /** check four directions */
        if (x-1 >= 0) {
            if (grid[x][y] == '.' || grid[x][y] == grid[x-1][y]) {
                if (visited[x-1][y] == -1) {
                    visited[x-1][y] = visited[x][y];
                    qu.push({x-1, y});
                } else {
                    union_sets(visited[x][y], visited[x-1][y]);
                }
            }
        }

        if (x + 1 < n) {
            if (grid[x][y] == '.' || grid[x][y] == grid[x+1][y]) {
                if (visited[x+1][y] == -1) {
                    visited[x+1][y] = visited[x][y];
                    qu.push({x+1, y});
                } else {
                    union_sets(visited[x][y], visited[x+1][y]);
                }
            }
        }

        if (y - 1 >= 0) {
            if (grid[x][y] == '.' || grid[x][y] == grid[x][y-1]) {
                if (visited[x][y-1] == -1) {
                    visited[x][y-1] = visited[x][y];
                    qu.push({x, y-1});
                } else {
                    union_sets(visited[x][y], visited[x][y-1]);
                }
            }
        }

        if (y + 1 < m) {
            if (grid[x][y] == '.' || grid[x][y] == grid[x][y+1]) {
                if (visited[x][y+1] == -1) {
                    visited[x][y+1] = visited[x][y];
                    qu.push({x, y+1});
                } else {
                    union_sets(visited[x][y], visited[x][y+1]);
                }
            }
        }
    }

    /** then process queries */
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        if (find_set(visited[a][b]) == find_set(visited[c][d])) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int test = 1;
    cin >> test;
    for (int t = 0; t < test; t++) {
        solve();
    }
}