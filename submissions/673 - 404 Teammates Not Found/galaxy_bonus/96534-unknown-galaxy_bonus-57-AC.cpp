#include<bits/stdc++.h>
using namespace std;

int n,m;
char g[205][205];
int id[205][205];
int a[40005],b[40005];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
//1 -1 0 0, 0 0 1 -1 
void bfs(int x,int y,int k){
    int l=0,r=1;
    a[0]=x;
    b[0]=y;
    id[x][y]=k;

    while(l<r){
        x=a[l];
        y=b[l];
        l++;
        for(int i=0;i<4;i++){
            int u=x+dx[i],v=y+dy[i];

            if(u<0||u>=n||v<0||v>=m){
                continue;
            }
            if(id[u][v]!=0){
                continue;
            }
            if(g[x][y]!='.'&&g[u][v]!='.'&&g[x][y]!=g[u][v]){
                continue;
            }
            id[u][v]=k;
            a[r]=u;
            b[r]=v;
            r++;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int q;
        cin>>n>>m>>q;
        for(int i=0;i<n;i++){
            cin>>g[i];
            for(int j=0;j<m;j++){
                id[i][j]=0;
            }
        }
        int k=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(id[i][j]==0){
                    k++;
                    bfs(i,j,k);
                }
            }
        }
        while(q--){
            int x,y,u,v;
            cin>>x>>y>>u>>v;
            //cout<<id[x][y]<<" "<<id[u][v]<<"\n";
            if(id[x][y]==id[u][v]){
                cout<<"YES\n";
            }
            else{
                cout<<"NO\n";
            }
        }
    }
    return 0;
}
