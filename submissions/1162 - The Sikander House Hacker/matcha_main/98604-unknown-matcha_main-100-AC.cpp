#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

static char buf[1 << 25];
static size_t bl = 0, bp = 0;

static inline int gc() {
    if (bp == bl) {
        bl = fread(buf, 1, sizeof(buf), stdin);
        bp = 0;
        if (bl == 0) return -1;
    }
    return buf[bp++];
}

static inline ll readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    ll x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

static vector<pair<ll, ll>> bucket[31];
static ll C;

static inline void addRange(ll l, ll r) {
    if (l == r) {
        C ^= l;
        return;
    }
    int k = 63 - __builtin_clzll((unsigned long long)(l ^ r));
    C ^= (l >> (k + 1)) << (k + 1);
    ll m = (1LL << (k + 1)) - 1;
    bucket[k].push_back({l & m, r & m});
}

static ll g(ll a, ll b) {
    ll res = 0;
    while (true) {
        if (a < b) swap(a, b);
        if (b == 0) {
            res += a;
            break;
        }
        int ha = 63 - __builtin_clzll((unsigned long long)a);
        int hb = 63 - __builtin_clzll((unsigned long long)b);
        if (ha == hb) {
            res += (1LL << (ha + 1)) - 1;
            break;
        }
        res += 1LL << ha;
        a -= 1LL << ha;
    }
    return res;
}

int main() {
    int T = (int)readInt();
    string out;
    while (T--) {
        int n = (int)readInt();
        vector<ll> L(n), R(n);
        for (int i = 0; i < n; i++) L[i] = readInt();
        for (int i = 0; i < n; i++) R[i] = readInt();
        for (int k = 0; k < 31; k++) bucket[k].clear();
        C = 0;
        for (int i = 0; i < n; i++) addRange(L[i], R[i]);
        for (int K = 29; K >= 0; K--) {
            vector<pair<ll, ll>>& b = bucket[K];
            if (b.empty()) continue;
            ll P = 1LL << K;
            ll o = P - 1;
            ll cl = b[0].first, cr = b[0].second;
            for (size_t i = 1; i < b.size(); i++) {
                ll bl2 = b[i].first, br2 = b[i].second;
                ll Aa = o - cl, pa = cr - P;
                ll Ab = o - bl2, pb = br2 - P;
                ll mlo = max(g(Aa, Ab), g(pa, pb));
                ll mhi = max(g(Aa, pb), g(pa, Ab));
                cl = o - mhi;
                cr = P + mlo;
                C ^= P;
            }
            if (((C >> K) & 1) == 0) {
                C ^= P;
                addRange(0, cr & o);
            } else {
                addRange(cl & o, o);
            }
        }
        out += to_string(C);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}