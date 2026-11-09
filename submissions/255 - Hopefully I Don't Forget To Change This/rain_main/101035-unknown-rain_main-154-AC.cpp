#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        map<int,pair<vector<int>,vector<int>>> g;
        for(int i=0;i<n;i++){
            int x,y,z;
            char d;
            cin >> x >> y >> z >> d;
            auto &p = g[x+y];
            (d=='E' ? p.first : p.second).push_back(x);
        }
        int total = 0;
        for(auto [s,p] : g){
            auto a = p.first,b = p.second;
            sort(a.begin(),a.end());
            a.erase(unique(a.begin(),a.end()),a.end());
            sort(b.begin(),b.end());
            b.erase(unique(b.begin(),b.end()),b.end());
            total += k * (a.size()+b.size());
            for(auto i : a)
                total -= lower_bound(b.begin(),b.end(),i+k) - lower_bound(b.begin(),b.end(),i);
        }
        cout << total << endl;
    }
}
