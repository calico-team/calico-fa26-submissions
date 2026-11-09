#include<bits/stdc++.h>
using namespace std;
#define int long long 
#pragma GCC optimize("O3,unroll-loops")

int vis[202][202];
char grid[202][202];
int n,m,qu;

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

bool ins(int x,int y){
    return (x>=0 && x<n && y<m && y>=0);
}

int cc;
void dfs(int x,int y){
    vis[x][y]=cc;
    for(int q=0;q<4;q++){
        int nx=x+dx[q],ny=y+dy[q];
        if(!ins(nx,ny) || vis[nx][ny])continue;
        if(grid[x][y]=='B' && grid[nx][ny]=='R')continue;
        if(grid[x][y]=='R' && grid[nx][ny]=='B')continue;
        dfs(nx,ny);
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int tc; cin>>tc;
    while(tc--){

        cc=0;
        cin>>n>>m>>qu;
        for(int q=0;q<n;q++){
            for(int w=0;w<m;w++){
                vis[q][w]=0;
                cin>>grid[q][w];
            }
        }

        for(int q=0;q<n;q++){
            for(int w=0;w<m;w++){
                if(vis[q][w])continue;
                cc++;
                dfs(q,w);
            }
        }

        while(qu--){
            int rs,cs,re,ce; cin>>rs>>cs>>re>>ce;
            if(vis[rs][cs]!=vis[re][ce]){
                cout<<"NO"<<endl;
            }
            else{
                cout<<"YES"<<endl;
            }
        }
    }
}