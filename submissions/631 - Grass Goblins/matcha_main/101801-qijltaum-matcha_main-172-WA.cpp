#include <bits/stdc++.h>
using namespace std;

#include <cassert>

#define lf "\n"
#define ff endl
#define fi first
#define se second
#define _ << ' ' <<
#define all(x) begin(x),end(x)
#define rall(x) rbegin(x),rend(x)

#ifdef DEBUG

constexpr bool IS_DEBUG = 1;

#define infor(fmt, ...) do { print(stderr, fmt, ##__VA_ARGS__); } while(0)
#define infof(fmt, ...) do { println(stderr, fmt, ##__VA_ARGS__); } while(0)

#else

constexpr bool IS_DEBUG = 0;

#define infor(fmt, ...)
#define infof(fmt, ...)

#endif /* DEBUG */

using ll = long long;

using pll = pair<ll, ll>;
using pii = pair<int, int>;

template<typename... Args>
using vec = vector<Args...>;

mt19937 timmy_loves_gambling(73);

constexpr int LOG = 30;

void solve(void) {
    int N; cin >> N;

    vec<int> L(N), R(N);
    for(auto &x: L) cin >> x;
    for(auto &x: R) cin >> x;

    vector is_fixed(N, vec<bool>(LOG));
    vec<int> V(N), fix_one(LOG), fix_zero(LOG);
    for(int i = 0; i < N; ++i) {
        for(int lg = LOG - 1; lg >= 0; lg--) {
            const int pow = 1 << lg;
            if((L[i]&pow) != (R[i]&pow)) break;
            is_fixed[i][lg] = 1;
            if(L[i]&pow) {
                fix_one[lg] += 1;
            } else {
                fix_zero[lg] += 1;
            }
        }

        R[i] += 1;

        for(int lg = 1; lg <= LOG; ++lg) {
            const int pow = 1 << lg;
            if((R[i]&(~(pow-1))) - pow < L[i]) break;
            V[i] = lg;
        }
    }

    int mx = 0;
    for(int i = 0; i < N; ++i) {
        int x = (1 << V[i]) - 1;
        int new_r = (R[i]&(~((1<<V[i])-1)))-1;
        for(int lg = V[i]; lg < LOG; ++lg) {
            const int pow = 1 << lg;
            int o = fix_one[lg];
            int z = fix_zero[lg];

            if(!is_fixed[i][lg]) {
                if(new_r & pow) {
                    o += 1;
                } else {
                    z += 1;
                }
            }

            int n = N - o - z;

            if(n > 0 || (o&1)) {
                x |= pow;
            }
        }

        mx = max(x, mx);
    }

    cout << mx << lf;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int T; cin >> T;
    while(T--) solve();
}
