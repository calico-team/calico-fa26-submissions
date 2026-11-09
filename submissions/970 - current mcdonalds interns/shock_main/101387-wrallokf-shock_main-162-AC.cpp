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
struct Q {int x, y, p;}; //earthquake center and power
vec<Q> eq;
vec<vec<int>> ans, nx; //readings and links to the next unfilled columns
//find the next unfilled column in the grid (doesnt have to be sequential)
int find(int r, int c) {
    while (nx[r][c]!=c) {
        nx[r][c] = nx[r][nx[r][c]]; //shorten links to skip filled cells faster
        c = nx[r][c];
    }
    return c;
}
inline void solve() {
    int n, m, q; cin>>n>>m>>q;
    eq.resize(q); //since we have q quakes, ensure itll fit
    for (auto &e:eq) cin>>e.x>>e.y>>e.p; //for every quake within eq, take its center / power to compute with later
    ans.assign(n, vec<int>(m, 0)); nx.assign(n, vec<int>(m+1));
    for (int r=0; r<n; r++) for (int c=0; c<=m; c++) nx[r][c] = c;
    for (int i=q-1; i>=0; i--) { //inversely iterate over the quakes
        int r = eq[i].x, c = eq[i].y, p = eq[i].p; //r and c at epicenter and then power of quake
        for (int row=r-p; row<=r+p; row++) { //for each row thats within the quakes range,
            int dr = row-r; //take the distance from the epicenter to the row,
            int width = sqrt(p*p-dr*dr); //the circle covers c+-width so we can just apply conics math
            int col = find(row, c-width); //find some column that satisfies the row we have and left bound
            while (col<=c+width) { //iter over every column until the right bound,
                int dc = col-c; //for every distance from found column to center,
                ans[row][col] = p*p-dr*dr-dc*dc+1; //log cell reading from power formula
                nx[row][col] = find(row, col+1); //mark it as filled so we dont recheck it
                col = nx[row][col]; //move on to the next column
            }
        }
    }
    for (auto &row:ans) {
        for (int x:row) cout<<x<<" "; //output every value line by line
        cout<<endl;
    }
}
int main() {
    //str fn = ""; fio(fn);
    fast;
    int t; cin>>t;
    while (t--) solve();
    return 0;
}

