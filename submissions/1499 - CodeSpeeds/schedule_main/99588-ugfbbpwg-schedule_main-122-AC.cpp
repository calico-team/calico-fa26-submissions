#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define all(x) x.begin(), x.end()
#define int long long

signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int tc=1;
    cin>>tc;
    auto solve=[&]()->void{
        int n;
        int m;
        int k;
        cin>>n>>m>>k;
        vi a(n+1);
        vector<vi> s(n+1);
        for(int i=1;i<=n;i++){
            cin>>a[i];
            if(a[i]){
                s[a[i]].push_back(i);
            }
        }
        vi d(n+1,-1);
        auto z=[&](auto&&q,int w){
            if(d[w]!=-1){
                return d[w];                
            }
            d[w]=1;
            for(int e:s[w]){
                d[w]=max(d[w],q(q,e)+1);
            }
            return d[w];
        };
        for(int i=1;i<=n;i++){
            z(z,i);
        }
        priority_queue<pair<int,int>> l;
        for(int i=1;i<=n;i++){
            if(a[i]==0){
                l.push({d[i],i});
            }
        }
        int r=0;
        for(int i=0;i<m&&!l.empty()&&r<n;i++){
            vi g;
            for(int j=0;j<k&&!l.empty();j++){
                int t=l.top().second;
                l.pop();
                r++;
                g.push_back(t);
            }
            for(int y:g){
                for(int u:s[y]){
                    l.push({d[u],u});
                }
            }
        }
        int output=r;
        cout<<output<<"\n";
    };
    for(int i=0;i<tc;i++){
        solve();
    }
    return 0;
}