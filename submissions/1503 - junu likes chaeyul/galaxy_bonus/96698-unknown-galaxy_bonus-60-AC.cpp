#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD=1e9+7,MAXF=2000005,INF=1e18,INV=5e8+4;

void solve(){
    int n,m;cin>>n>>m;
    int q;cin>>q;
    vector<string> grid(n);
    for(int i=0;i<n;i++) cin>>grid[i];
    //connected components impl type beat
    vector<vector<int>> comp(n,vector<int>(m,-1));
    pair<int,int> dir[]={{1,0},{-1,0},{0,1},{0,-1}};
    int c=0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(comp[i][j]!=-1) continue;

            queue<pair<int,int>> qu;
            qu.push({i,j});
            comp[i][j]=c;
            while(!qu.empty()){
                int x=qu.front().first,y=qu.front().second;
                qu.pop();
                for(int k=0;k<4;k++){
                    int nx=x+dir[k].first,ny=y+dir[k].second;
                    if(nx<0||nx>=n || ny<0 || ny>=m) continue;
                    if(comp[nx][ny]!=-1) continue;
                    // err ts not connected
                    if((grid[nx][ny]=='B' && grid[x][y]=='R')||(grid[nx][ny]=='R' && grid[x][y]=='B')) continue;
                    comp[nx][ny]=c;
                    qu.push({nx,ny});
                }
            }
            c++;
        }
    }
    for(int i=0;i<q;i++){
        int r1,c1,r2,c2;cin>>r1>>c1>>r2>>c2;
        if(comp[r1][c1]==comp[r2][c2]) cout<<"YES\n";
        else cout<<"NO\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    cin>>t;
    while(t--) solve();

}