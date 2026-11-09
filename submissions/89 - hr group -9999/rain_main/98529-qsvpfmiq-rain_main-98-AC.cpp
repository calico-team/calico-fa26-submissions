#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int t,n,k;
const int MAXN = 1e5+10;
vector<pair<int,int>> stuff;
set<array<int,3>> bruh;
vector<int> st[MAXN*2];

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    while(t--){
        cin >> n >> k;
        stuff.clear();
        bruh.clear();
        for(int i=0; i<MAXN*2; ++i) st[i].clear();

        ll base = 0;

        for(int i=1,x,y,z; i<=n; ++i){
            cin >> x >> y >> z;
            char d; cin >> d;
            d = (d == 'N');

            if(bruh.find({x,y,d}) != bruh.end()) continue;
            
            bruh.insert({x,y,d});
            base += k;

            if(d) st[x+y].push_back(x);
            else stuff.push_back({x,y});
        }

        for(int i=0; i<MAXN*2; ++i) sort(st[i].begin(),st[i].end());

        ll res = 0;
        for(auto[x,y] : stuff){
            int a = upper_bound(st[x+y].begin(),st[x+y].end(),x+k-1) - st[x+y].begin();
            int b = lower_bound(st[x+y].begin(),st[x+y].end(),x) - st[x+y].begin();
            res += a-b;
        }

        cout << base-res << "\n";
    }
}