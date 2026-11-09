#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
const int N = 200010;
pii a[N];
char type[N];
struct POI{
    int x;
    int y1;
    int y2;
    int type; // 0 start 1 north 2 end
    bool operator < (const POI & other)const{
        if(x == other.x) type < other.type;
        return x < other.x;
    }
};
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T;
    cin >> T;
    while(T--){
        int n, k;
        cin >> n >> k;
        vector<pii> north;
        vector<pii> east;
        vector<POI> sweep;
        for(int i = 1; i <= n; i++){
            cin >> a[i].first >> a[i].second;
            int z;
            cin >> z;
            char type;
            cin >> type;
            if(type == 'N'){
                north.pb(a[i]);
                sweep.pb({a[i].first, a[i].second, a[i].second+k, 1});
            }else{
                east.pb(a[i]);
                sweep.pb({a[i].first, a[i].second, a[i].second, 0});
                sweep.pb({a[i].first+k, a[i].second, a[i].second, 2});
            }
        }
        Tree<int> active;
        ll ans = 1LL*k*n;
        sort(sweep.begin(), sweep.end());
        for(auto i : sweep){
            //cout << i.type << " " << i.x << " " << i.y1 << " " << i.y2 << endl;
            if(i.type == 0){
                active.insert(i.y1);
            }else if(i.type == 1){
                ans -= (active.order_of_key(i.y2)-active.order_of_key(i.y1));
            }else if(i.type == 2){
                active.erase(i.y1);
            }
        }
        cout << ans << endl;
    }
    return 0;
}