#include <bits/stdc++.h>

using namespace std;

#define int long long
#define pb push_back
#define pii pair<int,int>


void calc(){
    int n, m;
    cin >> n >> m;
    vector<pii> north,east;
    for (int i=0;i<n;i++){
        int x,y,z;
        char c;
        cin >> x >> y >> z >> c;
        if (c=='N'){
            north.pb({x,y});
        }else{
            east.pb({x,y});
        }
    }
    map<int,vector<int>> a;
    for (auto [x,y]:east){
        a[y-north[0].second+x].pb(y);
    }
    // for (auto [key,val]:a){
    //     for (auto o:val){
    //         cout << key << " " << o << endl;
    //     }
    // }
    // cout << endl;
    int cnt = 0;
    for (auto [x,y]:north){
        int ny=y-north[0].second;
        int z = x+ny;
        auto val = a[z];
        int l=0,r=val.size();
        sort(val.begin(),val.end());
        // cout << val.size() << endl;
        while(l<r){
            int mid = (l+r)/2;
            int time = val[mid]-y;
            // cout << time << " " << val[mid] << endl;
            if (time<m){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        // cout << l << endl;
        cnt+=l;
    }
    cout << n*m-cnt << endl;
    
}

signed main() {
    int t;
    cin >> t;
    while(t--){
        calc();
    }
}
