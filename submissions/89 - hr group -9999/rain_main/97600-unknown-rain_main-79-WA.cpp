#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
typedef long long ll;

int t,n,k;
const int MAXN = 1e5+10;
vector<array<int,4>> stuff;

set<array<int,3>> bruh;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> st[2][MAXN*2];

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> t;
    while(t--){
        cin >> n >> k;
        stuff.clear();

        for(int i=1,x,y,z; i<=n; ++i){
            cin >> x >> y >> z;
            char d; cin >> d;
            d = (d == 'N');
            stuff.push_back({z,x,y,d});
        }

        sort(stuff.begin(),stuff.end(),greater<array<int,4>>());

        for(int i=0; i<MAXN*2; ++i){
            st[0][i].clear();
            st[1][i].clear();
        }

        ll ans = n*k;

        for(auto[z,x,y,d] : stuff){
            int v = x+y;

            if(bruh.find({x,y,d}) != bruh.end()) {
                ans -= k;
                continue;
            }

            if(d){
                int cnt = st[1][v].order_of_key(y+k) - st[1][v].order_of_key(y-1);
                ans -= cnt;

                st[0][v].insert(x);
            } else {
                int cnt = st[0][v].order_of_key(x+k) - st[0][v].order_of_key(x-1);
                ans -= cnt;

                st[1][v].insert(y);
            }
        }

        cout << ans << "\n";
    }
}