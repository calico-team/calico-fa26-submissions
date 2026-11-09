#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int B = 30;

struct State {
    ll pre;
    array<int, B> cnt;
    bool operator<(const State &o) const {
        if (pre != o.pre) return pre < o.pre;
        return cnt < o.cnt;
    }
    bool operator==(const State &o) const { return pre == o.pre && cnt == o.cnt; }
};

ll solve(const vector<ll> &L, const vector<ll> &R) {
    int n = L.size();
    ll K = 0;
    vector<vector<pair<ll, ll>>> groups(B);
    for (int i = 0; i < n; i++) {
        ll l = L[i], r = R[i];
        if (l == r) {
            K ^= l;
            continue;
        }
        int b = 63 - __builtin_clzll(l ^ r);
        ll mask = (1LL << b) - 1;
        K ^= (l >> (b + 1)) << (b + 1);
        groups[b].push_back({mask - (l & mask), r & mask});
    }
    int Kbit[B];
    bool need[B];
    ll Kc = K;
    for (int j = B - 1; j >= 0; j--) {
        int Kj = (Kc >> j) & 1;
        Kbit[j] = Kj;
        need[j] = false;
        if (!groups[j].empty()) {
            auto &els = groups[j];
            int v = els.size();
            int rho = 1 ^ Kj;
            int n1 = 0;
            for (auto &e : els)
                if (e.second >= e.first) n1++;
            need[j] = ((n1 & 1) != rho);
            Kc ^= (ll)rho << j;
            if ((v + rho) & 1) Kc ^= (1LL << j) - 1;
        }
    }
    vector<State> states(1);
    states[0].pre = 0;
    states[0].cnt.fill(0);
    ll bestDead = -1;
    for (int j = B - 1; j >= 0; j--) {
        vector<State> nxt;
        if (!groups[j].empty()) {
            auto &els = groups[j];
            array<int, B> baseAdd;
            baseAdd.fill(0);
            for (auto &e : els) {
                ll lim = max(e.first, e.second);
                for (int k = 0; k < j; k++)
                    if ((lim >> k) & 1) baseAdd[k]++;
            }
            vector<pair<ll, ll>> cands;
            if (need[j]) {
                cands = els;
                sort(cands.begin(), cands.end());
                cands.erase(unique(cands.begin(), cands.end()), cands.end());
            }
            for (auto &s : states) {
                if (s.cnt[j] >= 1) {
                    bestDead = max(bestDead, s.pre | ((1LL << (j + 1)) - 1));
                    continue;
                }
                ll pre2 = s.pre | (1LL << j);
                State ns;
                ns.pre = pre2;
                for (int k = 0; k < B; k++) ns.cnt[k] = s.cnt[k] + (k < j ? baseAdd[k] : 0);
                if (!need[j]) {
                    nxt.push_back(ns);
                } else {
                    for (auto &c : cands) {
                        ll m = max(c.first, c.second), nn = min(c.first, c.second);
                        State t = ns;
                        for (int k = 0; k < j; k++) t.cnt[k] += (int)((nn >> k) & 1) - (int)((m >> k) & 1);
                        nxt.push_back(t);
                    }
                }
            }
        } else {
            for (auto &s : states) {
                int d = s.cnt[j], Kj = Kbit[j];
                if (d >= 2 || (d == 1 && Kj == 1)) {
                    bestDead = max(bestDead, s.pre | ((1LL << (j + 1)) - 1));
                    continue;
                }
                int bit = (d == 1) ? 1 : Kj;
                State t = s;
                t.pre |= (ll)bit << j;
                nxt.push_back(t);
            }
        }
        if (!nxt.empty()) {
            ll mp = 0;
            for (auto &s : nxt) mp = max(mp, s.pre);
            vector<State> keep;
            for (auto &s : nxt)
                if (s.pre == mp) keep.push_back(s);
            if (j > 0 && (mp | ((1LL << j) - 1)) < bestDead) keep.clear();
            sort(keep.begin(), keep.end());
            keep.erase(unique(keep.begin(), keep.end()), keep.end());
            // dominance prune (capped at 2) when the set is small
            if (keep.size() > 1 && keep.size() <= 2000) {
                int sz = keep.size();
                vector<char> dead(sz, 0);
                for (int a = 0; a < sz; a++) {
                    if (dead[a]) continue;
                    for (int b = 0; b < sz; b++) {
                        if (a == b || dead[b]) continue;
                        bool le = true;
                        for (int k = 0; k < j && le; k++)
                            if (min(keep[b].cnt[k], 2) > min(keep[a].cnt[k], 2)) le = false;
                        // keep[b] <= keep[a] pointwise -> b dominated
                        if (le) {
                            bool eq = true;
                            for (int k = 0; k < j && eq; k++)
                                if (min(keep[b].cnt[k], 2) != min(keep[a].cnt[k], 2)) eq = false;
                            if (!eq || b > a) dead[b] = 1;
                        }
                    }
                }
                vector<State> k2;
                for (int a = 0; a < sz; a++)
                    if (!dead[a]) k2.push_back(keep[a]);
                keep.swap(k2);
            }
            states.swap(keep);
        } else {
            states.clear();
        }
    }
    ll res = bestDead;
    for (auto &s : states) res = max(res, s.pre);
    return res;
}

#ifndef FUZZ
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<ll> L(n), R(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        for (int i = 0; i < n; i++) cin >> R[i];
        cout << solve(L, R) << "\n";
    }
}
#endif
