#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define int long long
#define pii pair<int,int>
#define tiii tuple<int,int,int>

using namespace std;
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>

string o;

void solve(){
    int n,k;
    cin >> n >> k;
    vector<tiii> arr(n);
    vector<char> dir(n);
    for(int i = 0; i < n; i++){
        int x,y,z;
        cin >> x >> y >> z;
        cin >> dir[i];
        arr[i] = {x,y,z};
    }

    map<int,ordered_set> occ;
    for(int i = 0; i < n; i++){
        int x,y,z;
        tie(x,y,z) = arr[i];
        if(dir[i] == 'N') occ[x+y].insert(x);
    }

    int cnt = 0;
    for(int i = 0; i < n; i++){
        if(dir[i] == 'N') {
            cnt += k;
            continue;
        }
        int x,y,z;
        tie(x,y,z) = arr[i];
        // if(occ)
        int bad = 0; 
        bad += occ[x+y].order_of_key(x+k);
        bad -= occ[x+y].order_of_key(x+1);
        cnt += k-bad;
    }
    cout << cnt << "\n";
}
int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        solve();
    }

    //cout << o << endl;
}