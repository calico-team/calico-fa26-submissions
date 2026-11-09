#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
void fio(const std::string& fn) {freopen((fn+".in").c_str(), "r", stdin); freopen((fn+".out").c_str(), "w", stdout);}
#define vec vector
#define str string
#define mp make_pair
#define pii pair<int, int>
#define pll pair<ll, ll>
#define fi first
#define se second
#define fr front
#define bk back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()
#define rep(i, st, end) for (int i=(st); i<(end); i++)
#define arrin(a) for (auto &x:(a)) cin>>x
#define cont continue
#define accum accumulate
#define sum(a) accum(all(a), 0LL)
#define pb push_back
#define pf push_front
#define ppb pop_back
#define ppf pop_front
#define uset unordered_set
#define umap unordered_map
#define umset unordered_multiset
#define hmap hash_map
#define hmset hash_multiset
#define hset hash_set
#define mset multiset
#define que queue
#define dq deque
#define pq priority_queue
#define dpq pq<int, vec<int>, greater<int>>
#define ipq pq<int, vec<int>, less<int>>
typedef unsigned long long ull;
typedef unsigned int ui;
typedef long double ld;
typedef long long ll;
using namespace std;
struct ST {int x, y, c;}; //x pos y pos color
inline void solve() {
    int n, m, q; cin>>n>>m >>q; //n = row, m = col, q = quers
    vector<string> grid(n); arrin(grid);
    //reach[X][Y][COLOR] means we can get to the target from pos (x,y) in that color mode
    vec<vec<array<bool, 2>>> reach(n, vector<array<bool, 2>>(m));
    stack<ST> sts; //holds the states we need to check for reaching targ

    // Work backwards: start at the destination in each possible mode.
    for (int i=0; i<2; i++) { //i is the state iterator
        char k = (i==0?'B':'R'); //what state are we in
        if (grid[n-1][m-1]=='.'||grid[n-1][m-1]==k) { //if the last tile is empty or matches our state,
            reach[n-1][m - 1][i] = true; //it is reachable
            sts.push({n-1, m-1, i}); //and push to stack to check from that pos
        }
    }
    int dx[] = {-1, 1, 0, 0}; //change in row/col for directions
    int dy[] = {0, 0, -1, 1};
    while (!sts.empty()) { //go through every node in the stack
        ST c = sts.top(); sts.pop(); //just take the current one then get rid of it instead of later,
        int x = c.x; int y = c.y; int col = c.c;
        int oppo = (col==0?1:0); //oppo state
        if (grid[x][y]=='.'&&!reach[x][y][oppo]) { //if its a normal tile and we havent seen the opposite mode,
            reach[x][y][oppo] = 1; //we can spin from the opposite mode and reach the target too
            sts.push({x, y, oppo}); //then push the same tile in the opposite mode to check next
        }
        //any active neighbor can reach this tile in the current mode
        for (int i=0; i<4; i++) { //up down left right
            int nx = x+dx[i]; //next row to check on
            int ny = y+dy[i]; //next col to check on
            if (nx<0||nx>=n||ny<0||ny>=m) continue; //bounds check for hte next coord so we dont die
            if (reach[nx][ny][col]) continue;
            char tl = grid[nx][ny]; //tile at the next pos
            char acol = (col==0?'B':'R'); //the active color we are in
            if (tl!='.'&&tl!=acol) continue;
            //if the tile is not empty and not the same color as the active color we cannot go there
            reach[nx][ny][col] = true; //otherwise the neighbor can reach this tile, and then the target
            sts.push({nx, ny, col}); //so we throw this next position onto the stack to check from it next,
        }
    }
    //NOTE: EVERY QUERY STARTS IN BLUE
    while (q--) {
        int stx, sty, ndx, ndy; cin>>stx>>sty>>ndx>>ndy; //per query inputs
        if (reach[stx][sty][0]) cout<<"YES\n"; //just check the built arr for the pos / color = 0
        else cout<<"NO\n";
    }
}
int main() {
    //str fn = "5"; fio(fn);
    fast;
    int t; cin>>t;
    while (t--) solve();
    return 0;
}

