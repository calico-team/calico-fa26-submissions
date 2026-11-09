#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cmath>
#include <numeric>
#include <queue>
#include <stack>
#include <iomanip>
#include <array>
#include <functional>
#include <bitset>
using namespace std;

void baseIO(string s = "") {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    if (s.size()) {
        freopen((s + ".in").c_str(), "r", stdin);
        freopen((s + ".out").c_str(), "w", stdout);
    }
}

int subcount = 376;

#define ll long long
#define db long double
#define all(x) (x).begin(), (x).end()

struct drone {
    int x;
    int y;
    int z;
    char d;
};

void solve() {
    int n;
    ll k;
    cin >> n >> k;

    vector<drone> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].x >> a[i].y >> a[i].z >> a[i].d;
    }

    ll ans = n * k;

    map<int, vector<int>> east;
    for (auto &dr : a) {
        if (dr.d == 'E') {
            east[dr.x + dr.y].push_back(dr.y);
        }
    }

    for (auto &p : east) {
        sort(all(p.second));
    }

    for (auto &dr : a) {
        if (dr.d == 'N') {
            auto it = lower_bound(all(east[dr.x + dr.y]), k + dr.y);
            ans -= it - lower_bound(all(east[dr.x + dr.y]), dr.y);
        }
    }

    cout << ans;
}

signed main() {
    baseIO();

    int t;
    cin >> t;
    while (t--){
        solve(), cout << endl;
    }

    return 0;
}