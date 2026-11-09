#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull =unsigned long long;
using ull32= uint32_t;
const int BITS =30;
const uint32_t FULL = (1u <<BITS)- 1;
uint32_t bestInRange(uint32_t c,uint32_t L, uint32_t R) {
    uint32_t pref =0;
    for(int b = BITS- 1; b >= 0; --b) {
        uint32_t bit= 1u << b;
        int want = 1 ^ ((c >> b)& 1u);
        uint32_t cand =pref | (want ? bit : 0u);
        uint64_t lo =cand;
        uint64_t hi= lo + bit -1;
        if (lo <=R&& hi >= L)
            pref= cand;
        else
            pref|= want ? 0u : bit;
    }
    return pref;
}
uint32_t exactDP(
    const vector<uint32_t>& L,
    const vector<uint32_t>& R,
    uint32_t fixedXor
) {
    int n =L.size();
    int states = 1<< (2 * n);
    vector<int32_t> memo((BITS +1)* states, -1);
    function<uint32_t(int, int)>dfs =
        [&](int bit, int code) -> uint32_t {
        if (bit <0) return 0;
        int idx =bit* states + code;
        if (memo[idx]!= -1)
            return (uint32_t)memo[idx];
        uint32_t best= 0;
        for(int mask= 0; mask < (1 << n); ++mask) {
            int nc = 0;
            bool ok =true;
            int parity = __builtin_popcount((unsigned)mask) ^((fixedXor >>bit) & 1u);
            for(int i =0; i< n; ++i) {
                int st =(code >> (2* i)) & 3;
                int lt = st& 1;
                int ht =(st >> 1) & 1;
                int lb = (L[i]>> bit) & 1u;
                int rb= (R[i] >> bit) & 1u;
                int xb = (mask >>i)& 1;
                if((lt && xb <lb) || (ht && xb > rb)) {
                    ok =false;
                    break;
                }
                int nlt = lt && (xb== lb);
                int nht =ht && (xb == rb);
                nc |= (nlt | (nht<< 1)) << (2 *i);
            }
            if (!ok) continue;
            uint32_t cand=((uint32_t)(parity & 1) <<bit) |dfs(bit - 1, nc);
            best =max(best, cand);
        }
        return memo[idx] =(int32_t)best;
    };
    return dfs(BITS - 1, states -1);
}
uint32_t bruteSmall(
    const vector<uint32_t>& L,
    const vector<uint32_t>& R,
    uint32_t fixedXor
) {
    int n= L.size();
    uint32_t best = 0;
    function<void(int, uint32_t)>go =
        [&](int i, uint32_t cur) {
        if(i ==n) {
            best = max(best, cur);
            return;
        }
        for(uint32_t x= L[i];; ++x) {
            go(i + 1, cur ^x);
            if (x ==R[i]) break;
        }
    };
    go(0, fixedXor);
    return best;
}
uint32_t localSearch(
    const vector<uint32_t>& L,
    const vector<uint32_t>& R,
    uint32_t fixedXor,
    mt19937_64& rng
) {
    int n =L.size();
    if (n== 0) return fixedXor;
    uint32_t best= 0;
    vector<uint32_t> xs(n);
    vector<int> order(n);
    iota(order.begin(),order.end(), 0);
    auto run =[&](int mode) {
        if (mode == 0){
            for (int i= 0; i < n; ++i)
                xs[i]= L[i];
            iota(order.begin(), order.end(),0);
        }
        else if (mode ==1){
            for (int i = 0; i <n; ++i)
                xs[i]= R[i];
            for(int i = 0;i <n; ++i)
                order[i] = n -1 - i;
        }
        else if (mode ==2){
            for (int i = 0; i< n; ++i)
                xs[i] =L[i] + (R[i] - L[i])/ 2;
            iota(order.begin(), order.end(),0);
        }
        else if (mode == 3){
            for (int i= 0;i < n; ++i) {
                uint64_t len =(uint64_t)R[i] - L[i] + 1;
                xs[i] =L[i] + (uint32_t)(rng()% len);
            }
            iota(order.begin(), order.end(), 0);
            shuffle(order.begin(), order.end(), rng);
        }
        else if(mode ==4) {
            for (int i = 0; i < n;++i)
                xs[i] = (rng() & 1) ? L[i] : R[i];
            iota(order.begin(), order.end(), 0);
            shuffle(order.begin(), order.end(), rng);
        }
        else{
            for (int i = 0; i < n;++i) {
                uint64_t len = (uint64_t)R[i] - L[i] + 1;
                xs[i] =L[i] +(uint32_t)(rng() % len);
            }
            for (int i = 0; i < n; ++i)
                order[i] = n - 1 -i;
            shuffle(order.begin(), order.end(), rng);
        }
        uint32_t total =fixedXor;
        for (uint32_t x : xs)
            total^= x;
        if(total == FULL) {
            best =FULL;
            return;
        }
        for (int sweep =0; sweep < 10; ++sweep) {
            bool changed= false;
            for(int id : order) {
                uint32_t other = total ^xs[id];
                uint32_t nx=bestInRange(other, L[id], R[id]);
                if(nx != xs[id]) {
                    total = other ^nx;
                    xs[id] =nx;
                    changed= true;
                    if (total == FULL){
                        best =FULL;
                        return;
                    }
                }
            }
            if (!changed) break;
        }
        best =max(best, total);
    };

    for (int mode = 0; mode< 6 && best != FULL;++mode)
        run(mode);
    return best;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >>T;
    mt19937_64 rng(0x8f3f73b5cf1c9ad7ULL);
    ll dpBudget = 30000000LL;
    ll bruteBudget= 20000000LL;
    while (T--){
        int N;
        cin>> N;
        vector<uint32_t> L(N),R(N);
        for (auto &x : L) cin >> x;
        for(auto &x : R) cin>> x;
        uint32_t fixedXor = 0;
        vector<uint32_t> a,b;
        a.reserve(N);
        b.reserve(N);
        ll product =1;
        bool productSmall = true;
        for (int i =0; i< N; ++i) {
            if(L[i] == R[i]) {
                fixedXor ^=L[i];
            } else{
                a.push_back(L[i]);
                b.push_back(R[i]);
                uint64_t len=(uint64_t)R[i] - L[i] +1;
                if (product >2000 / (ll)len) {
                    productSmall = false;
                }
                else if (productSmall) {
                    product*= (ll)len;
                }
            }
        }
        int m =a.size();
        uint32_t ans;
        if (m == 0) {
            ans= fixedXor;
        }
        else if(
            productSmall &&
            product <= 2000 &&
            product <=bruteBudget
        ) {
            ans =bruteSmall(a, b, fixedXor);
            bruteBudget -= product;
        }
        else{
            ll cost = (m <=6)
                ? 30LL * (1LL<< (3 * m))
                : LLONG_MAX;
            if(m <= 6 && cost <= dpBudget) {
                ans = exactDP(a,b, fixedXor);
                dpBudget -=cost;
            }
            else{
                ans = localSearch(a, b,fixedXor, rng);
            }
        }
        cout << ans<< '\n';
    }
    return 0;
}