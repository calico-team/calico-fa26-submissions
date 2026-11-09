#include <bits/stdc++.h>
using namespace std;

// clang-format off
#define int long long
#define double long double
#define pii pair<int, int>
#define endl "\n"
#define prec(i) fixed << setprecision(i)
#define all(v) (v.begin()), (v.end())
#define rall(v) (v.rbegin()), (v.rend())
#define pc __builtin_popcountll
const int INF = 1e18;
const int MOD = 1e9 + 7;
// const int MOD = 998244353;

#ifndef ONLINE_JUDGE
template<class...T>ostream& operator<<(ostream&s,const pair<T...>&p){return s<<"("<<p.first<<", "<<p.second<<")";}
#define PR(C) template<class...T>ostream& operator<<(ostream&s,const C<T...>&v){s<<"{";int n=0;for(auto&x:v)s<<(n++?", ":"")<<x;return s<<"}";}
PR(vector)PR(set)
template<class...T>ostream& operator<<(ostream&s,const map<T...>&v){s<<"{";int n=0;for(auto&[k,x]:v)s<<(n++?", ":"")<<k<<": "<<x;return s<<"}";}
template<class T,class...U>void _dbg(const T&x,const U&...y){cerr<<x;((cerr<<", "<<y),...);cerr<<endl;}
#define dbg(...) do{cerr<<"["<<#__VA_ARGS__<<"]: ";_dbg(__VA_ARGS__);}while(0)
#else
#define dbg(...)
#endif

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define each(i, v) for (auto& i : (v))

int cdiv(int a, int b) { return a / b + ((a ^ b) > 0 && a % b); }
int fdiv(int a, int b) { return a / b - ((a ^ b) < 0 && a % b); }

template <class T> bool chmax(T& a, T b, bool isok = true) { return isok && a < b ? a = b, 1 : 0; }
template <class T> bool chmin(T& a, T b, bool isok = true) { return isok && b < a ? a = b, 1 : 0; }
// clang-format on

// const int N = M = 205;
const int N = 205;
const int M = 205;

int n, m, q;
char g[N][M];
bool visited[N][M];
int dir[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

bool bfs(pii s, pii e) {
    memset(visited, false, sizeof(visited));
    queue<pii> q;
    q.push(s);
    visited[s.first][s.second] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        // if (x == e.first && y == e.second) {
        //     return true;
        // }

        rep(i, 4) {
            int newx = x + dir[i][0];
            int newy = y + dir[i][1];
            if (newx < 0 || newx >= n || newy < 0 || newy >= m || visited[newx][newy]) {
                continue;
            }

            if ((g[newx][newy] == 'R' || g[newx][newy] == 'B') &&
                (g[x][y] == 'R' || g[x][y] == 'B') && g[x][y] != g[newx][newy]) {
                continue;
            }

            visited[newx][newy] = true;
            q.push({newx, newy});
        }
    }

    return visited[e.first][e.second];
}

void solve(int tc) {
    cin >> n >> m >> q;

    rep(i, n) cin >> g[i];

    pii br = {n - 1, m - 1};
    bfs(br, br);

    while (q--) {
        pii s, e;
        cin >> s.first >> s.second >> e.first >> e.second;
        cout << (visited[s.first][s.second] == true ? "YES" : "NO") << endl;
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int t = 1;
    cin >> t;

    rep1(tc, t) {
        solve(tc);
    }
}
