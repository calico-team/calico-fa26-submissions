#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define int long long
#define all(x) (x).begin(), (x).end()
#define forn(var,start,end) for(int var=start;var<end;var++)
#define X first
#define Y second

void solve(){
    string s;
    int n;
    cin>>s>>n;
    vector<int> a(n+1,0);

    if(s=="FIRST"){
        vector<vector<int>> adj(n+1);
        forn(i,0,n-1){
            int x,y;
            cin>>x>>y;
            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        queue<int> qu;
        qu.push(1);
        while(!qu.empty()){
            int x=qu.front();
            qu.pop();

            forn(i,0,adj[x].size()){
                int y=adj[x][i];
                if(y==a[x]) continue;
                a[y]=x;
                qu.push(y);
            }
        }

        forn(i,2,n+1) a[1]^=a[i];
        forn(i,1,n+1){
            if(i>1) cout<<' ';
            cout<<a[i];
        }
        cout<<'\n';
    }
    else{
        int pos=0,sum=0;
        forn(i,1,n+1){
            cin>>a[i];
            if(a[i]==-1) pos=i;
            else sum^=a[i];
        }

        a[pos]=sum;
        forn(i,2,n+1){
            cout<<i<<' '<<a[i]<<'\n';
        }
    }
    //yesssirr

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}