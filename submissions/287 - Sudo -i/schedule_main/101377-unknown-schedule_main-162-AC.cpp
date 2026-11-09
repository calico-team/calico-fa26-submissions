#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
const int N=10005,M=50005;
int p[N],dep[N],cnt[M]={0};

int dfs(int cur){
    if(dep[cur]!=-1) return dep[cur];
    return dep[cur]=dfs(p[cur])+1;
}

void solve(){
    int n,m,k,cur=0,res=0;
    scanf("%d %d %d",&n,&m,&k);
    memset(dep,-1,sizeof(dep));
    memset(cnt,0,sizeof(cnt));
    for(int i=1; i<=n; i++){
        scanf("%d",&p[i]);
        if(p[i]==0) dep[i]=0;
    }
    for(int i=1; i<=n; i++)
        if(dep[i]==-1) cnt[dfs(i)]++;
        else cnt[dep[i]]++;
    for(int i=0; i<m; i++) cur+=cnt[i],res=min(res+k,cur);
    printf("%d\n",res);
}

int main(){
    //freopen("p6.in","r",stdin);
    //freopen("p6.out","w",stdout);
    int t;
    scanf("%d",&t);
    while(t--) solve();
    return 0;
}