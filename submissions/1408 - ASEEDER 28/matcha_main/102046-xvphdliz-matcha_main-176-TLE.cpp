#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 正确做法：可达成的 XOR 集合 = 各区间 [L_i,R_i] 在 XOR-Minkowski 意义下的折叠。
 * 把区间拆成 O(log) 个对齐的 dyadic 块；两块 [x,x+2^p) 与 [y,y+2^q) 的 XOR
 * 恰好是一个对齐区间。把当前可达成集合维护成若干互不相交的区间并逐段合并即可。
 * 实验上区间个数极小（通常 ≤ 5），总复杂度约 O(N * B^2)，B=30。
 */

static vector<pair<long long, int>> decompose(long long L, long long R) {
    vector<pair<long long, int>> out;
    while (L <= R) {
        int p = 0;
        while (p < 30 && ((L & ((1LL << (p + 1)) - 1)) == 0) &&
               L + (1LL << (p + 1)) - 1 <= R)
            ++p;
        out.push_back({L, p});
        L += 1LL << p;
    }
    return out;
}

static pair<long long, long long> dyadicXor(long long x, int p, long long y, int q) {
    if (p < q) {
        swap(x, y);
        swap(p, q);
    }
    long long mask = (1LL << p) - 1;
    long long base = (x ^ y) & ~mask;
    return {base, base + mask};
}

static vector<pair<long long, long long>> mergeIvs(vector<pair<long long, long long>> ivs) {
    if (ivs.empty()) return ivs;
    sort(ivs.begin(), ivs.end());
    vector<pair<long long, long long>> out;
    out.push_back(ivs[0]);
    for (size_t i = 1; i < ivs.size(); ++i) {
        if (ivs[i].first <= out.back().second + 1)
            out.back().second = max(out.back().second, ivs[i].second);
        else
            out.push_back(ivs[i]);
    }
    return out;
}

static vector<pair<long long, long long>>
xorWithRange(const vector<pair<long long, long long>>& ivs, long long L, long long R) {
    auto dyNew = decompose(L, R);
    vector<pair<long long, long long>> neu;
    neu.reserve(ivs.size() * 32 * dyNew.size());
    for (auto [a, b] : ivs) {
        for (auto [x, p] : decompose(a, b)) {
            for (auto [y, q] : dyNew)
                neu.push_back(dyadicXor(x, p, y, q));
        }
    }
    return mergeIvs(std::move(neu));
}

long long solve(int n, const vector<long long>& L, const vector<long long>& R) {
    vector<pair<long long, long long>> ivs = {{L[0], R[0]}};
    for (int i = 1; i < n; ++i)
        ivs = xorWithRange(ivs, L[i], R[i]);
    long long ans = 0;
    for (auto [a, b] : ivs) ans = max(ans, b);
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<long long> L(n), R(n);
        for (auto& x : L) cin >> x;
        for (auto& x : R) cin >> x;
        cout << solve(n, L, R) << '\n';
    }
}
