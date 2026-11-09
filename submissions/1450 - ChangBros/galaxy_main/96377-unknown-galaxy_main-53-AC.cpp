#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

int n,m;
vector<string> v;
vector<vector<int>> vis;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};

void floodfill(int r,int c){
    queue<pair<int,int>> qu;
    qu.push({r,c});
    vis[r][c]=1;

    while(!qu.empty()){
        int x=qu.front().X, y=qu.front().Y;
        qu.pop();

        forn(i,0,4){
            int nx=x+dx[i], ny=y+dy[i];
            if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
            if(vis[nx][ny]) continue;
            if(v[x][y]!='.' && v[nx][ny]!='.' &&
               v[x][y]!=v[nx][ny]) {continue;
               }

            vis[nx][ny]=1;
            qu.push({nx,ny});
        }
    }
}

void solve(){
    int t;
    cin>>t;
    while(t--){
        int q;
        cin>>n>>m>>q;
        v.resize(n);
        forn(i,0,n) cin>>v[i];
        vis.assign(n,vector<int>(m,0));

        floodfill(n-1,m-1);

        while(q--){
            int a,b,c,d;
            cin>>a>>b>>c>>d;
            if(vis[a][b]) {
                cout<<"YES"<<endl;
            }
            else cout<<"NO"<<endl;
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}