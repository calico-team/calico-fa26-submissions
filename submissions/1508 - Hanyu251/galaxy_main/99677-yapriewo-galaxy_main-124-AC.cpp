#include<bits/stdc++.h>
using namespace std;
#define printf if(false)

int to(int x,int y){
    return 201*x+y;
}

vector<int>parent(to(200,200)+1);
vector<int>s(to(200,200)+1);

int find(int x){
    if(x==parent[x])return x;
    parent[x]=find(parent[x]);
    return parent[x];
}

void join(int x,int y){
    x=find(x),y=find(y);
    if(s[x]>s[y])swap(x,y);
    parent[x]=y;
}

void solve(){
    int n,m,q;cin>>n>>m>>q;
    for(int x=0;x<n;++x){
        for(int y=0;y<m;++y){
            parent[to(x,y)]=to(x,y);
            s[to(x,y)]=1;
        }
    }
    vector<vector<char>>grid(n,vector<char>(m));
    for(int x=0;x<n;++x){
        for(int y=0;y<m;++y){
            cin>>grid[x][y];

        }
    }
    for(int x=0;x<n;++x){
        for(int y=0;y<m;++y){
            if(x<n-1)if(grid[x][y]=='.'||grid[x+1][y]=='.'||grid[x][y]==grid[x+1][y])join(to(x,y),to(x+1,y));
            if(y<m-1)if(grid[x][y]=='.'||grid[x][y+1]=='.'||grid[x][y]==grid[x][y+1])join(to(x,y),to(x,y+1));
        }
    }

    for(int i=0;i<q;++i){
        int sx,sy,ex,ey;cin>>sx>>sy>>ex>>ey;
        cout<<(find(to(sx,sy))==find(to(ex,ey))?"YES":"NO")<<endl;
    }
}
int main(){
    cin.tie(nullptr);
    cin.sync_with_stdio(false);
    int t;cin>>t;while(t--){
        solve();
    }
}
