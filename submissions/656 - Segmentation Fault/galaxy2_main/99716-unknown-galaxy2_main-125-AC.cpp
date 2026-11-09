#include <bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define FORR(i,a,b) for(int i=(b)-1;i>=(a);--i)
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define bk back()
typedef long long ll;
typedef pair<int,int> pii;
const int N=4005,INF=1e9+1;

int dep[N],par[N],sub[N];
bool vis[N];
struct p {
    int x, y;
    char c; int n;
};
struct qu {
    int r1, c1, r2, c2, k, ans;
};
char mp[15][N];
int dist[20][15][N][2];
qu qs[100005];
int ord[100005];
int n, m;
int dx[]={1,-1,0,0},dy[] = {0,0,1,-1};

void bfs(int r1,int c1,char c,int id,int lo,int hi){
    FOR(i,0,n) FOR(j,lo,hi+1) dist[id][i][j][0] = dist[id][i][j][1]=INF;
    queue<p> q; //bool visited[15][4005] = {};
    q.push({r1, c1, c, 0}); dist[id][r1][c1][c=='R'] = 0;
    while(!q.empty()){
        p top = q.front(); q.pop();
        int b = top.c=='R';
        FOR(d,0,4){
            int x = top.x+dx[d], y=top.y+dy[d];
            if(x < 0 || x>=n || y < lo || y > hi) continue;
            if(mp[x][y] != '.' && mp[x][y] != top.c) continue;
            if(dist[id][x][y][b] != INF) continue;
            dist[id][x][y][b]=top.n+1;
            q.push({x,y,top.c,top.n+1});
        }
        if(mp[top.x][top.y] == '.' && dist[id][top.x][top.y][!b] == INF){
            dist[id][top.x][top.y][!b] = top.n+1;
            q.push({top.x, top.y, b?'B':'R', top.n+1});
        }
    }
}

void solve(){
    int q;cin >> n >> m >> q;
    FOR(i,0,n) FOR(j,0,m) cin >> mp[i][j];

    int cnt = 0;
    while(q--){
        int r1, c1, r2, c2, k;cin >> r1 >> c1 >> r2 >> c2 >> k;
        // bfs(r1, c1, r2, c2, k);
        qs[cnt]={r1,c1,r2,c2,k,2000000009};
        ord[cnt] = cnt; cnt++;
    }

    auto go=[&](auto&&go,int lo,int hi,int l,int r)->void{
        if(l >= r) return;
        int mid = (lo+hi)/2, cnt=0;
        FOR(i,0,n){
            if(mp[i][mid] != 'R') bfs(i,mid,'B',cnt++,lo,hi);
            if(mp[i][mid]!='B') bfs(i,mid,'R',cnt++,lo,hi);
        }
        FOR(i,l,r){
            qu &u = qs[ord[i]];
            FOR(j,0,cnt) u.ans=min(u.ans, dist[j][u.r1][u.c1][0]+min(dist[j][u.r2][u.c2][0],dist[j][u.r2][u.c2][1]));
        }

        int x = partition(ord+l,ord+r,[&](int j){
            return qs[j].c1<mid && qs[j].c2<mid;
        })-ord;
        int y = partition(ord+x,ord+r,[&](int j){
            return qs[j].c1>mid && qs[j].c2>mid;
        })-ord;
        go(go,lo,mid-1,l,x);
        go(go,mid+1,hi,x,y);
    };
    go(go,0,m-1,0,cnt);


    FOR(i,0,cnt) cout << (qs[i].ans <= qs[i].k ? "YES\n":"NO\n");
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;
    while(t--) solve();
}
