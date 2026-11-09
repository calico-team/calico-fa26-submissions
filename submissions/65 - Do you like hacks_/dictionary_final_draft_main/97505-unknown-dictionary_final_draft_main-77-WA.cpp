#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+5, M=60*N;
int a[N], b[N];
vector<int> e[N];
int rd[N];
int vis[N];
int son[M][2], siz[M], fa[M], cnt=1;
void modify(int x, int v, int dt){
    for(int i=29; i>=0; --i){
        int c=v>>i&1;
        if(!son[x][c]) son[x][c]=++cnt, fa[cnt]=x;
        x=son[x][c];
    }
    while(x){
        siz[x]+=dt;
        x=fa[x];
    }
}
int query(int x, int v){
    int ans=0;
    for(int i=29; i>=0; --i){
        int c=v>>i&1;
        if(son[x][c^1]&&siz[son[x][c^1]]) c^=1, ans^=1<<i;
        assert(son[x][c]&&siz[son[x][c]]);
        x=son[x][c];
    }
    return ans;
}
int res[N];
void dfs(int x, int ff, int rt, int pre, int bs){
    if(x!=rt) pre^=b[x];
    // cerr << "DEBUG: " << x << ' ' << pre << ' ' << bs << '\n';
    res[x]=max(query(1,pre),query(1,pre^bs));
    modify(1,pre,1);
    for(auto y:e[x]){
        if(y==ff||y==rt) continue;
        dfs(y, x, rt, pre, bs);
    }
    modify(1,pre,-1);
}
int main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for(int i=1; i<=n; ++i){
            rd[i]=0;
            res[i]=-1;
            e[i].clear();
        }
        for(int i=1; i<=n; ++i){
            cin >> a[i];
            rd[a[i]]++;
            e[a[i]].push_back(i);
        }
        for(int i=1; i<=n; ++i){
            cin >> b[i];
        }
        {
            queue<int> q;
            for(int i=1; i<=n; ++i){
                if(!rd[i]) q.push(i);
            }
            while(!q.empty()){
                int x=q.front(); q.pop();
                rd[a[x]]--; if(!rd[a[x]]) q.push(a[x]);
            }
        }
        for(int i=1; i<=n; ++i){
            vis[i]=0;
        }
        for(int i=1; i<=n; ++i){
            if(rd[i]&&!vis[i]){
                int x=i;
                int v=0;
                do{
                    modify(1,v,1);
                    v^=b[x], vis[x]=1;
                    x=a[x];
                }while(x!=i);
                dfs(x,0,x,0, v);
                v=0;
                do{
                    modify(1,v,-1);
                    v^=b[x], x=a[x];
                }while(x!=i);
            }
        }
        // cout << "Result: ";
        for(int i=1; i<=n; ++i){
            cout << res[i] << " \n"[i==n];
        }
        // cerr << "";
    }
    return 0;
}