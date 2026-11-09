#include <bits/stdc++.h>
using namespace std;
using ll=long long int;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
using pli=pair<ll,int>;
using pil=pair<int,ll>;
using vi=vector<int>;
using vll=vector<ll>;
using vc=vector<char>;
using vvc=vector<vc>;
using vb=vector<bool>;
using vvb=vector<vb>;
using vvi=vector<vi>;
using vvll=vector<vll>;
using vpii=vector<pii>;
using vpll=vector<pll>;
using vvpii=vector<vpii>;
using vvpll=vector<vpll>;

void dfs(vvi &graph,vector<vvb> &visited,int y,int x,int c,int n,int m) {
    for (pii p : vpii{{0,1},{1,0},{0,-1},{-1,0}}) {
        int yy=y+p.first;
        int xx=x+p.second;
        if (yy>=0 && yy<n && xx>=0 && xx<m) {
            if (graph[yy][xx]==2) {
                if (!visited[yy][xx][0]) {
                    visited[yy][xx][0]=true;
                    dfs(graph,visited,yy,xx,0,n,m);
                }
                if (!visited[yy][xx][1]) {
                    visited[yy][xx][1]=true;
                    dfs(graph,visited,yy,xx,1,n,m);
                }
            }
            else if (graph[yy][xx]==c) {
                if (!visited[yy][xx][c]) {
                    visited[yy][xx][c]=true;
                    dfs(graph,visited,yy,xx,c,n,m);
                }
            }
        }
    }
}

int main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n,m,q;
        cin >> n >> m >> q;
        vvi graph(n,vi(m));
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                char c;
                cin >> c;
                if (c=='R') graph[i][j]=0;
                else if (c=='B') graph[i][j]=1;
                else graph[i][j]=2;
            }
        }
        vector<vvb> visited(n,vvb(m,vb(2,false)));
        if (graph[n-1][m-1]!=1) {
            visited[n-1][m-1][0]=true;
            dfs(graph,visited,n-1,m-1,0,n,m);
        }
        if (graph[n-1][m-1]!=0) {
            visited[n-1][m-1][1]=true;
            dfs(graph,visited,n-1,m-1,1,n,m);
        }
        while (q--) {
            int sy,sx;
            int ey,ex;
            cin >> sy >> sx >> ey >> ex;
            if (visited[sy][sx][1]) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}