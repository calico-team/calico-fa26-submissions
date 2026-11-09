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
    vec<vec<array<int, 2>>> reach(n, vector<array<int, 2>>(m));
    stack<ST> sts; //holds the states we need to check for this group

    int dx[] = {-1, 1, 0, 0}; //change in row/col for directions
    int dy[] = {0, 0, -1, 1};
    int grp = 0; //grp counter;
    //groups are sets of tiles that can reach each other in a single color state
    //start a DFS for each state that hasnt been put in a group
    for (int x=0; x<n; x++) { //for each x pos
        for (int y=0; y<m; y++) { //for each y pos
            for (int col=0; col<2; col++) { //for colors
        char k = (col==0?'B':'R'); //what state are we in
        if (reach[x][y][col]||(grid[x][y]!='.'&&grid[x][y]!=k)) continue;
        //if we have already seen pos, tile is not empty, AND tile is not same color as state, we do not have req to make group
        grp++; //otherwise we do
        reach[x][y][col] = grp; //we need to log this pos as a group for this state,
        sts.push({x, y, col}); //push to stack to check from that pos
    while (!sts.empty()) { //go through every node in the stack
        ST c = sts.top(); sts.pop(); //just take the current one then get rid of it instead of later,
        int x = c.x; int y = c.y; int col = c.c;
        int oppo = (col==0?1:0); //oppo state
        if (grid[x][y]=='.'&&!reach[x][y][oppo]) { //if its a normal tile and we havent seen the opposite mode,
            reach[x][y][oppo] = grp; //we can spin to the opposite mode in this group
            sts.push({x, y, oppo}); //then push the same tile in the opposite mode to check next
        }
        //any active neighbor can reach this tile in the current mode
        for (int i=0; i<4; i++) { //up down left right
            int nx = x+dx[i]; //next row to check on
            int ny = y+dy[i]; //next col to check on
            if (nx<0||nx>=n||ny<0||ny>=m) continue; //bounds check for hte next coord so we dont die
            if (reach[nx][ny][col]) continue; //if we have seen this pos skip
            char tl = grid[nx][ny]; //tile at the next pos
            char acol = (col==0?'B':'R'); //the active color we are in
            if (tl!='.'&&tl!=acol) continue;
            //if the tile is not empty and not the same color as the active color we cannot go there
            reach[nx][ny][col] = grp; //otherwise this neighbor can reach the tile, -> then target from there
            sts.push({nx, ny, col}); //so we throw this next position onto the stack to check from it next,
        }
    }
    }}}
    while (q--) {
        int stx, sty, ndx, ndy; cin>>stx>>sty>>ndx>>ndy; //we start from anywhere now
        int start = reach[stx][sty][0]; //starts in blue, 
        if (start==reach[ndx][ndy][0] || start==reach[ndx][ndy][1]) cout<<"YES\n"; //can end in either mode
        else cout<<"NO\n";
    }//note, problem changes since we have to now work from any point on the grid not just the corner;
    //we can use dfs still probably, just now we have to treat the states neighboring each other as connected components, and then check if the start and end are in the same component (pretty sure since we arent guarnteed to get an empty tile i think)
}
int main() {
    //str fn = "5"; fio(fn);
    fast;
    int t; cin>>t;
    while (t--) solve();
    return 0;
}

