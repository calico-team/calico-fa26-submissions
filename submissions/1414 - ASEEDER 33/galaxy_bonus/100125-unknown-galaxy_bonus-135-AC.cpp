#include<bits/stdc++.h>
using namespace std;
int fa[500001];
int findfa(int x){
    if(fa[x]==x)return x;
    fa[x]=findfa(fa[x]);
    return fa[x];
}
void merge(int x,int y){
    int fx=findfa(x);
    int fy=findfa(y);
    if(fx!=fy)fa[fx]=fy;
}
int id(int x,int y,int m,int mode){
    return (x*m+y)*2+mode;
}
char g[201][201];
int main(){
    ios::sync_with_stdio(false);
    int t;
    cin>>t;
    while(t--){
        int n,m,q;
        cin>>n>>m>>q;
        for(int i=0;i<n*m*2;i++)fa[i]=i;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cin>>g[i][j];
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(g[i][j]=='.')merge(id(i,j,m,0),id(i,j,m,1));
                if(j+1<m){
                    char a=g[i][j],b=g[i][j+1];
                    if(a=='B'&&b=='B'||a=='.'||b=='.')merge(id(i,j,m,0),id(i,j+1,m,0));
                    if(a=='R'&&b=='R'||a=='.'||b=='.')merge(id(i,j,m,1),id(i,j+1,m,1));
                }
                if(i+1<n){
                    char a=g[i][j],b=g[i+1][j];
                    if(a=='B'&&b=='B'||a=='.'||b=='.')merge(id(i,j,m,0),id(i+1,j,m,0));
                    if(a=='R'&&b=='R'||a=='.'||b=='.')merge(id(i,j,m,1),id(i+1,j,m,1));
                }
            }
        }
        while(q--){
            int sx,sy,ex,ey;
            cin>>sx>>sy>>ex>>ey;
            int sid=id(sx,sy,m,0);
            int eid;
            if(g[ex][ey]=='R')eid=id(ex,ey,m,1);
            else if(g[ex][ey]=='B'||g[ex][ey]=='.')eid=id(ex,ey,m,0);
            if(findfa(eid)==findfa(sid))cout<<"YES"<<endl;
            else cout<<"NO"<<endl;
        }
    }
    return 0;
}