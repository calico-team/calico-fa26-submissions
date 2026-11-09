#include <iostream>
#include <vector>
#include <map>
#include <array>
#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace std;
using namespace __gnu_pbds; 
#define fast ios_base::sync_with_stdio(0) , cin.tie(0)
using ll=long long;
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

struct D{
    int x;
    int y;
    int z;
    char d;
};

void solve() {
    int n,k;
    cin >> n >> k;
    vector<D> L(n);
    for (int i =0;i<n;i++){
        cin >> L[i].x >> L[i].y >> L[i].z >> L[i].d;
    }
    sort(L.begin(),L.end(),[](D a, D b){return a.z>b.z;});

    map<int,ordered_set> mN;
    map<int,ordered_set> mE;

    ll ans=0;
    for (int i =0;i<n;i++){
        // cout << "PROCESS " << L[i].x << " " << L[i].y << " " << L[i].z <<" "<< L[i].d <<endl;
        int curv = L[i].x+L[i].y;
        // cout << "CURV " << curv << endl;
    
        if(L[i].d=='N'){
            //pair with E, must be before
            int it2 = mE[curv].order_of_key(L[i].x);
            int it1 = mE[curv].order_of_key(L[i].x-(k-1));
            ans+=k-(it2-it1);
        } else {
            int it1 = mN[curv].order_of_key(L[i].x+1);
            int it2 = mN[curv].order_of_key(L[i].x+(k-1)+1);
            ans+=k-(it2-it1);
        }

        if(L[i].d=='N'){
            mN[curv].insert(L[i].x);
        }else{
            mE[curv].insert(L[i].x);
        }
    }
    cout << ans << endl;
}

signed main() {
    fast;
    int t;cin>>t;
    while (t--) solve();
    return 0;
}

