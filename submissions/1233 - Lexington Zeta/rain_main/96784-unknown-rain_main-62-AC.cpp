#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numeric>
#include <climits>
#include <random>
#include <queue>
#include <deque>
#include <chrono>
#include <bitset>
#include <functional>
#include <cstdio>
#include <cstring>
#define endl '\n'
#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4.1,sse4.2,avx,avx2,popcnt")
using namespace std;

#define IO cin.tie(0);cin.sync_with_stdio(0);
#define int long long
#define double long double
#define f first
#define s second
#define pb push_back
#define all(a) a.begin(), a.end()
#define MOD 998244353

using ll=long long;
using pii=pair<int, int>;
using pipii=pair<int, pii>;
using ppi=pair<pii, int>;
using ppipi=pair<pii,pii>;

template<typename T> using min_heap=priority_queue<T,vector<T>,greater<T>>;
template<typename T> using max_heap=priority_queue<T>;
template<typename T> using vv=vector<vector<T>>;
template<typename T> using vvv=vector<vector<vector<T>>>;

using vi=vector<int>;
using vpi=vector<pii>;
using vvi=vv<int>;
using vvpi=vv<pii>;
using vvvi=vvv<int>;
using vvvpi=vvv<pii>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rd(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
int inv(int a) { return (a <= 1 ? a : MOD - (long long)(MOD/a) * inv(MOD%a) % MOD); }
template<typename T, typename S> T ifloor(T a, S b) { return a/b - (a%b && (a^b) < 0); }
template<typename T, typename S> T iceil(T a, S b) { return ifloor(a + b - 1, b); }

void solve() {
    int n, k;
    cin >> n >> k;

    vector<ppi> a(n);
    vector<char> movements(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].f.f >> a[i].f.s >> a[i].s;
        cin >> movements[i];
    }

    map<int, set<int>> fake;
    for (int i = 0; i < n; ++i) {
        if (movements[i] == 'N') {
            int sum = a[i].f.f + a[i].f.s;
            fake[sum].insert(a[i].f.f);
        }
    }
    map<int, vi> north;
    for (auto [sum, x] : fake) {
        north[sum] = {};
        for (auto p : x) {
            north[sum].pb(p);
        }
    }

    int ans = n * k;
    for (int i = 0; i < n; ++i) {
        if (movements[i] == 'E') {
            int sum = a[i].f.f + a[i].f.s;
            if (north.count(sum)) {
                int it1 = (upper_bound(all(north[sum]), a[i].f.f + k - 1) - north[sum].begin());
                int it2 = (upper_bound(all(north[sum]), a[i].f.f) - north[sum].begin());
                ans -= it1 - it2;
            }
        }
    }
    cout << ans << endl;
}

signed main() {
    IO

    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}