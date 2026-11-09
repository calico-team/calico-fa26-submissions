#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

vector<int> a,v,deg,p,ans;
vector<vector<int>> adj;
vector<array<int32_t,3>> tr;

void add(int val,int d){
    int x=0;
    tr[x][2]+=d;

    for(int b=29;b>=0;b--){
        int bit=(val>>b)&1;

        if(tr[x][bit]==0){
            tr[x][bit]=(int32_t)tr.size();
            tr.push_back({0,0,0});
        }

        x=tr[x][bit];
        tr[x][2]+=d;
    }
}

int get(int val){
    int x=0,res=0;

    for(int b=29;b>=0;b--){
        int bit=(val>>b)&1;
        int y=tr[x][bit^1];

        if(y!=0 && tr[y][2]>0){
            res|=1LL<<b;
            x=y;
        }
        else x=tr[x][bit];
    }

    return res;
}
void dfs(int s){
    stack<pair<int,int>> st;
    st.push({s,0});

    while(!st.empty()){
        int x=st.top().X, done=st.top().Y;
        st.pop();

        if(done){
            add(p[x],-1);
            continue;
        }

        p[x]=v[x]^p[a[x]];
        ans[x]=get(p[x]);
        add(p[x],1);

        st.push({x,1});

        forn(i,0,(int)adj[x].size()){
            int y=adj[x][i];
            if(deg[y]==0) st.push({y,0});
        }
    }
}

void solve(){
    int t;
    cin>>t;

    while(t--){
        int n;
        cin>>n;

        a.resize(n+1);
        v.resize(n+1);
        deg.assign(n+1,0);
        p.assign(n+1,0);
        ans.assign(n+1,0);
        adj.assign(n+1,vector<int>());

        forn(i,1,n+1){
            cin>>a[i];
            deg[a[i]]++;
            adj[a[i]].push_back(i);
        }

        forn(i,1,n+1) cin>>v[i];

        queue<int> qu;
        forn(i,1,n+1){
            if(deg[i]==0) qu.push(i);
        }

        while(!qu.empty()){
            int x=qu.front();
            qu.pop();

            int y=a[x];
            deg[y]--;
            if(deg[y]==0) qu.push(y);
        }

        vector<int> vis(n+1,0);
        tr.reserve(32*n+1);

        forn(i,1,n+1){
            if(deg[i]==0 || vis[i]) continue;

            vector<int> cyc;
            int x=i,sum=0;

            do{
                cyc.push_back(x);
                vis[x]=1;
                p[x]=sum;
                sum^=v[x];
                x=a[x];
            }while(x!=i);

            tr.clear();
            tr.push_back({0,0,0});

            forn(j,0,(int)cyc.size()){
                x=cyc[j];
                add(p[x],1);
                if(sum!=0) add(p[x]^sum,1);
            }

            forn(j,0,(int)cyc.size()){
                x=cyc[j];
                ans[x]=get(p[x]);

                forn(k,0,(int)adj[x].size()){
                    int y=adj[x][k];
                    if(deg[y]==0) dfs(y);
                }
            }
        }

        forn(i,1,n+1){
            if(i>1) cout<<' ';
            cout<<ans[i];
        }
        cout<<'\n';
    }
    //yeessssirboi
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}