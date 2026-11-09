#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct Block {
    int s, k;
    bool operator<(const Block& o) const {
        return s < o.s || (s == o.s && k < o.k);
    }
};

vector<Block> decompose(int l, int r) {
    vector<Block> v;
    while (l <= r) {
        int k = (l == 0 ? 30 : __builtin_ctz((unsigned)l));
        while ((1LL << k) > (ll)r - l + 1) --k;
        v.push_back({l, k});
        l += (1 << k);
    }
    return v;
}

vector<Block> normalize(vector<Block>& v) {
    sort(v.begin(), v.end());

    vector<pair<ll,ll>> intervals;
    for (auto b : v) {
        ll l = b.s;
        ll r = l + (1LL << b.k) - 1;

        if (!intervals.empty() && l <= intervals.back().second + 1) {
            intervals.back().second = max(intervals.back().second, r);
        } else {
            intervals.push_back({l,r});
        }
    }

    vector<Block> ans;
    for (auto [l,r] : intervals) {
        auto x = decompose((int)l, (int)r);
        ans.insert(ans.end(), x.begin(), x.end());
    }
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

        vector<int> L(n), R(n);
        for (int &x : L) cin >> x;
        for (int &x : R) cin >> x;

        vector<Block> cur = {{0,0}};

        for (int i = 0; i < n; ++i) {
            auto d = decompose(L[i], R[i]);

            vector<Block> nxt;
            for (auto a : cur) {
                for (auto b : d) {
                    int k = max(a.k, b.k);
                    int s = (((a.s >> k) ^ (b.s >> k)) << k);
                    nxt.push_back({s,k});
                }
            }

            cur = normalize(nxt);
        }

        ll ans = 0;
        for (auto b : cur) {
            ans = max(ans, (ll)b.s + (1LL << b.k) - 1);
        }

        cout << ans << '\n';
    }
    return 0;
}