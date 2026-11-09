#include <iostream>
#include <string>
#include <cstring>
using namespace std;
int n,m,q;
string g[200];
int comp[200][200][2];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool active(int x,int y,int m) {
    if(g[x][y]=='.') return true;
    if(g[x][y]=='B') return m==0;
    return m==1;
}
void dfs(int x,int y,int m,int id) {
    if(x<0||x>=n||y<0||y>=m){
        return;
    }
    if(!active(x,y,m)||comp[x][y][m]!=-1){
        return;
    }
    comp[x][y][m]=id;
    for(int d=0;d<4;d++){
        dfs(x+dx[d],y+dy[d],m,id);
    }
    if(g[x][y]=='.'){
        dfs(x,y,1-m,id);
    }
}

int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=0;i<n;i++){
            cin>>g[i];
        }
        memset(comp,-1,sizeof(comp));
        int id=0;
        for(int x=0;x<n;x++){
            for(int y=0;y<m;y++){
                for(int m=0;m<2;m++){
                    if(active(x,y,m)&&comp[x][y][m]==-1){
                        dfs(x,y,m,id++);
                    }
                }
            }
        }
        while(q--){
            int rs,cs,re,ce;
            cin>>rs>>cs>>re>>ce;
            int s=comp[rs][cs][0];
            if(comp[re][ce][0]==s||comp[re][ce][1]==s){
                cout<<"YES"<<endl;
            }else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}