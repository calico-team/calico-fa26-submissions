#include<bits/stdc++.h>
using namespace std;
#define int long long 
#pragma GCC optimize("O3,unroll-loops")
const int maxn=1e5;

char grid[12][4002];
int n,m,qu;
int dist[22][12][4002][2];
int r1[maxn+2],c1[maxn+2],r2[maxn+2],c2[maxn+2],k[maxn+2];
int ans[maxn+2];

int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

bool ins(int x,int y){
    return (x>=0 && x<n && y<m && y>=0);
}

void bfs(int sx,int sy,int col,int l,int r,int root){
    for(int w=0;w<n;w++){
        for(int e=l;e<=r;e++){
            dist[root][w][e][0]=dist[root][w][e][1]=1e18;
        }
    }

    queue<array<int,3>>qu;
    dist[root][sx][sy][col]=0;
    qu.push({sx,sy,col});

    while(qu.size()){
        auto [x,y,p]=qu.front(); qu.pop();
        for(int w=0;w<4;w++){
            int nx=x+dx[w],ny=y+dy[w];
            if(nx<0 || nx>=n || ny<l || ny>r)continue;
            if(p==0 && grid[nx][ny]=='R')continue;
            if(p==1 && grid[nx][ny]=='B')continue;

            if(dist[root][nx][ny][p]>dist[root][x][y][p]+1){
                dist[root][nx][ny][p]=dist[root][x][y][p]+1;
                qu.push({nx,ny,p});
            }
        }

        if(grid[x][y]=='.'){
            if(dist[root][x][y][1-p]>dist[root][x][y][p]+1){
                dist[root][x][y][1-p]=dist[root][x][y][p]+1;
                qu.push({x,y,1-p});
            }
        }
    }
}

void dnc(int l,int r,vector<int>&idx){
    if(l>r || idx.empty())return;

    vector<int>valid;
    int mid=(l+r)/2;

    for(int col=0;col<2;col++){
        for(int q=0;q<n;q++){
            if(grid[q][mid]=='R' && col==0)continue;
            if(grid[q][mid]=='B' && col==1)continue;
            int root=q*2+col;
            valid.push_back(root);

            bfs(q,mid,col,l,r,root);
        }
    }

    vector<int>L,R;
    for(auto a : idx){
        if(max(c1[a],c2[a])<mid)L.push_back(a);
        if(min(c1[a],c2[a])>mid)R.push_back(a);

        for(auto root : valid){
            int x=dist[root][r1[a]][c1[a]][0];
            for(int e=0;e<2;e++){
                int y=dist[root][r2[a]][c2[a]][e];
                ans[a]=min(ans[a],x+y);
            }
        }
    }
    dnc(l,mid-1,L),dnc(mid+1,r,R);
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);

    int tc; cin>>tc;
    while(tc--){
        cin>>n>>m>>qu;
        for(int q=0;q<n;q++){
            for(int w=0;w<m;w++){
                cin>>grid[q][w];
            }
        }

        vector<int>solve;

        for(int q=1;q<=qu;q++){
            solve.push_back(q);
            ans[q]=1e18;
            cin>>r1[q]>>c1[q]>>r2[q]>>c2[q]>>k[q];
            
        }

        dnc(0,m-1,solve);
        for(int q=1;q<=qu;q++){
            if(ans[q]>k[q]){
                cout<<"NO"<<'\n';
            }
            else{
                cout<<"YES"<<'\n';
            }
        }
    }
}