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

void dfs(vvi &graph,vector<vvi> &visited,int y,int x,int c,int n,int m,int cnt) {
    for (pii p : vpii{{0,1},{1,0},{0,-1},{-1,0}}) {
        int yy=y+p.first;
        int xx=x+p.second;
        if (yy>=0 && yy<n && xx>=0 && xx<m) {
            if (graph[yy][xx]==2) {
                if (visited[yy][xx][0]==-1) {
                    visited[yy][xx][0]=cnt;
                    dfs(graph,visited,yy,xx,0,n,m,cnt);
                }
                if (visited[yy][xx][1]==-1) {
                    visited[yy][xx][1]=cnt;
                    dfs(graph,visited,yy,xx,1,n,m,cnt);
                }
            }
            else if (graph[yy][xx]==c) {
                if (visited[yy][xx][c]==-1) {
                    visited[yy][xx][c]=cnt;
                    dfs(graph,visited,yy,xx,c,n,m,cnt);
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
        vector<vvi> visited(n,vvi(m,vi(2,-1)));
        int cnt=0;
        for (int i=0; i<n; ++i) {
            for (int j=0; j<m; ++j) {
                if (graph[i][j]==2) {
                    if (visited[i][j][0]==-1) {
                        visited[i][j][0]=cnt;
                        dfs(graph,visited,i,j,0,n,m,cnt);
                        cnt++;
                    }
                    if (visited[i][j][1]==-1) {
                        visited[i][j][1]=cnt;
                        dfs(graph,visited,i,j,1,n,m,cnt);
                        cnt++;
                    }
                }
            }
        }
        while (q--) {
            int sy,sx;
            int ey,ex;
            cin >> sy >> sx >> ey >> ex;
            if (visited[sy][sx][1]==visited[ey][ex][0] || visited[sy][sx][1]==visited[ey][ex][1]) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}