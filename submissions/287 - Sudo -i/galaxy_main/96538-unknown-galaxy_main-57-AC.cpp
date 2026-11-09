#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
const int N=205;
int dir[4][2]={{1,0},{-1,0},{0,-1},{0,1}};
char s[N][N],res[N][N]={0},vis[N][N]={0};
int n,m,q;

void dfs(int x,int y){
    res[x][y]=vis[x][y]=1;
    for(int i=0; i<4; i++){
        int dx=x+dir[i][0],dy=y+dir[i][1];
        if(0<=dx && dx<n && 0<=dy && dy<m && (s[x][y]=='.' || s[dx][dy]=='.' || s[x][y]==s[dx][dy]) && !vis[dx][dy])
            dfs(dx,dy);
    }
}

void solve(){
    int x1,y1,x2,y2;
    scanf("%d %d %d",&n,&m,&q);
    for(int i=0; i<n; i++) scanf("%s",s[i]);
    memset(res,0,sizeof(res));
    memset(vis,0,sizeof(vis));
    dfs(n-1,m-1);
    while(q--){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        if(res[x1][y1]==1) printf("YES\n");
        else printf("NO\n");
    }
}

int main(){
    //freopen("p5.in","r",stdin);
    //freopen("p5.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}