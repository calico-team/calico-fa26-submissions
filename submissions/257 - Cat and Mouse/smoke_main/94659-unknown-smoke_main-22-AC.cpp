#include <bits/stdc++.h>
using namespace std;

typedef long long i64;

template<class T>
using vec = vector<T>;
using p_ii = pair<int,int>;

#ifndef LOCAL
#define cerr if(false) cerr
#endif

void run() {
    int N, R;
    std::cin >> N >> R;
    std::vector<int> A(N);
    int smoke_charges = 2;
    int last_tick_time = 0; // when the last call was
    int last_tick_regen = 0; // progress to next smoke

    for (int& x: A) std::cin >> x;

    for (int& t: A) {
        int delta = t - last_tick_time;
        int regen = last_tick_regen + delta;
        smoke_charges = min(2, (smoke_charges + regen / R));
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

int main() {
    int T; std::cin >> T;
    for (int i=0; i<T; ++i) {
        run();
    }    

    return 0;
}