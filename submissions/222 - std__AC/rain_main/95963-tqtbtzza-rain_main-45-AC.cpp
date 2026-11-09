#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> BST;
const int N = 100100;
struct S {
    int x, y, z;
    char chr;
    bool operator<(S aa) const {
        return z < aa.z;
    }
} arr[N];
int t, n, k, ans;

signed main() {
    cin >> t;
    while (t--) {
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> arr[i].x >> arr[i].y >> arr[i].z >> arr[i].chr;
        }
        sort(arr + 1, arr + n + 1);
        map<int, BST> mpx;
        map<int, BST> mpy;
        ans = k * n;
        for (int i = n; i > 0; i--) {
            if ('E' == arr[i].chr) {
                ans -= mpx[arr[i].x + arr[i].y].order_of_key(arr[i].x + k) - mpx[arr[i].x + arr[i].y].order_of_key(arr[i].x);
                mpy[arr[i].x + arr[i].y].insert(arr[i].y);
            } else {
                ans -= mpy[arr[i].x + arr[i].y].order_of_key(arr[i].y + k) - mpy[arr[i].x + arr[i].y].order_of_key(arr[i].y);
                mpx[arr[i].x + arr[i].y].insert(arr[i].x);
            }
        }
        cout << ans << endl;
    }
    return 0;
}