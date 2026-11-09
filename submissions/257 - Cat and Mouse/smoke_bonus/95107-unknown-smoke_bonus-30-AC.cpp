#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef long long i64;

template<class T>
using vec = vector<T>;
using p_ii = pair<int,int>;

#ifndef LOCAL
#define cerr if(false) cerr
#endif



const int MAX_N = 100007;
int arr[MAX_N];

void run() {
    int N, R;
    std::cin >> N >> R;
    int smoke_charges = 2;
    int last_tick_time = 0; // when the last call was
    int last_tick_regen = 0; // progress to next smoke

    for (int i=0; i<N; ++i) std::cin >> arr[i];

    for (int i=0; i<N; ++i) {
        int t = arr[i];

        int delta = t - last_tick_time;
        int regen = last_tick_regen + delta;
        smoke_charges = min(2ll, (smoke_charges + regen / R));
        if (smoke_charges != 2) {
            last_tick_regen = regen % R;
        }
        else {
            last_tick_regen = 0;
        }
        if (smoke_charges == 0) {
            std::cout << "NO\n";
            return;
        }
        smoke_charges--;
        last_tick_time = t;
    }
    std::cout << "YES\n";

}

signed main() {
    cin.sync_with_stdio(0);
    cin.tie(0);
    int T; std::cin >> T;
    for (int i=0; i<T; ++i) {
        run();
    }    

    return 0;
}