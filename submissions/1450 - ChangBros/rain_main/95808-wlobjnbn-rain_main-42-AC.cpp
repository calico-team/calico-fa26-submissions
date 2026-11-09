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
        int n,k;
        cin>>n>>k;
        map<int,vector<int>> intmap;
        vector<pair<int,int>> v;

        forn(i,0,n){
            int x,y,z;
            char d;
            cin>>x>>y>>z>>d;
            if(d=='E') {intmap[x+y].push_back(x);
            }
            else v.push_back({x+y,x});
        }
        for(auto &p:intmap) sort(all(p.Y));

        int ans=n*k;

        forn(i,0,v.size()){
            int sum=v[i].X, x=v[i].Y;
            auto it=intmap.find(sum);
            if(it==intmap.end()) {continue;
            }

            auto &a=it->Y;
            int l=lower_bound(all(a),x-k+1)-a.begin();
            int r=lower_bound(all(a),x)-a.begin();
            ans=ans - (r-l);
        }
        cout<<ans<<endl;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
}