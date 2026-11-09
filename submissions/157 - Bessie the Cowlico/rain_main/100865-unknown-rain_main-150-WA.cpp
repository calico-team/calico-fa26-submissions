#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using LL = long long;
using str = string;
LL n;
struct pos {
    LL x, y, z;
};
typedef tree<
    LL, 
    null_type, 
    less<LL>, 
    rb_tree_tag, 
    tree_order_statistics_node_update
> ordered_set;
int main() {
    // freopen("usaco.in", "r", stdin);
    // freopen("usaco.out", "w", stdout);
    cin >> n;
    while (n--) {
        LL num_drones, num_days;
        cin >> num_drones >> num_days;
        vector<pos> drones_east;
        map<LL, ordered_set> diags;
        for (int i = 0; i < num_drones; ++i) {
            char dir;
            LL x, y, z;
            cin >> x >> y >> z >> dir;
            if (dir == 'E') drones_east.push_back({x, y, z});
            else diags[x+y].insert(y);
        }
        LL ctot = 0;
        for (auto& curr:drones_east) {
            auto& cset = diags[curr.x+curr.y];
            if (!cset.empty()) ctot += cset.size()-cset.order_of_key(curr.y-num_days+1);
        }
        cout << num_drones*num_days-ctot << '\n';
    }
}