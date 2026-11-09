
#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
const int conX=100000000;
int n,m,q;
string g[10];
int d[20][10][4000][2];
int rs[100000],cs[100000],re[100000],ce[100000],K[100000];
int best[100000];
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool act(int x,int y,int md){
    if(g[x][y]=='.') return true;
    if(g[x][y]=='B') return md==0;
    return md==1;
}
void bfs(int k,int sx,int mid,int smd,int l,int r){
    for(int x=0;x<n;x++){
        for(int y=l;y<=r;y++){
            d[k][x][y][0]=d[k][x][y][1]=conX;
        }
    }    
    queue<vector<int>> qu;
    d[k][sx][mid][smd]=0;
    qu.push({sx,mid,smd});
    while(!qu.empty()){
        vector<int> cur=qu.front();
        qu.pop();
        int x=cur[0],y=cur[1],md=cur[2];
        int dst=d[k][x][y][md];
        for(int i=0;i<4;i++){
            int nx=x+dx[i],ny=y+dy[i];
            if(nx<0||nx>=n||ny<l||ny>r) continue;
            if(!act(nx,ny,md)||d[k][nx][ny][md]!=conX) continue;
            d[k][nx][ny][md]=dst+1;
            qu.push({nx,ny,md});
        }
        if(g[x][y]=='.'&&d[k][x][y][1-md]==conX){
            d[k][x][y][1-md]=dst+1;
            qu.push({x,y,1-md});
        }
    }
}
void solve(int l,int r,vector<int> &qs) {
    if(l>r||qs.empty()) return;
    int mid=(l+r)/2;
    int cnt=0;
    vector<int> src;
    for(int x=0;x<n;x++){
        for(int md = 0; md < 2; md++){
            if(act(x,mid,md)){
                bfs(cnt++,x,mid,md,l,r);
            }
        }
    }    
    vector<int> left,right;
    for(int id : qs){
        if(ce[id]<mid&&cs[id]<mid){
            left.push_back(id);
        }else if(ce[id]>mid&&cs[id]>mid){
            right.push_back(id);
        }
        for(int k=0;k<cnt;k++){
            int a=d[k][rs[id]][cs[id]][0];
            if(a>=conX){
                continue;
            }
            for(int md=0;md<2;md++){
                int b=d[k][re[id]][ce[id]][md];
                if(b>=conX){
                    continue;
                }
                if(a+b<best[id]){
                    best[id]=a+b;
                }
            }
        }
    }
    solve(l,mid-1,left);
    solve(mid+1,r,right);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m>>q;
        for(int i=0;i<n;i++){
            cin>>g[i];
        }
        for(int i=0;i<q;i++){
            cin>>rs[i]>>cs[i]>>re[i]>>ce[i]>>K[i];
            best[i]=conX;
        }
        vector<int> all(q);
        for(int i=0;i<q;i++) all[i]=i;
        solve(0,m-1,all);
        for(int i=0;i<q;i++){
            if(best[i]<=K[i]){
                cout<< "YES"<<endl;
            }else{
                cout<<"NO"<<endl;
            }
        }
    }
    return 0;
}