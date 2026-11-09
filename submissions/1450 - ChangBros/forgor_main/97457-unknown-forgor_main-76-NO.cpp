#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

void solve(){
    int t;
    cin>>t;
    while(t--){
        int n,m,k;
        cin>>n>>m>>k;
        vector<vector<int>> adj(n+1);
        vector<int> depth(n+1,0),cnt(n+1,0);
        queue<int> qu;

        forn(i,1,n+1){
            int p;
            cin>>p;
            if(p==0){
                depth[i]=1;
                qu.push(i);
            }
            else adj[p].push_back(i);
        }
        while(!qu.empty()){
            int x=qu.front();
            qu.pop();
            cnt[depth[x]]++;

            forn(i,0,adj[x].size()){
                int y=adj[x][i];
                depth[y]=depth[x]+1;
                qu.push(y);
            }
        }

        int ans=min(n,m*k),sum=0;
        forn(i,1,min(n,m)+1){
            sum+=cnt[i];
            ans=min(ans,sum+(m-i)*k);
        }
        cout<<ans<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}