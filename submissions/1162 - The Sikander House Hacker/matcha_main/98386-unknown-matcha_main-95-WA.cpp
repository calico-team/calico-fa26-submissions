#include <bits/stdc++.h>
using namespace std;

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

static inline long long readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    long long x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

static vector<pair<long long, long long>> bucket[31];
static long long C;

static inline void addRange(long long l, long long r) {
    if (l == r) {
        C ^= l;
        return;
    }
    int k = 63 - __builtin_clzll((unsigned long long)(l ^ r));
    C ^= (l >> (k + 1)) << (k + 1);
    long long m = (1LL << (k + 1)) - 1;
    bucket[k].push_back({l & m, r & m});
}

int main() {
    int T = (int)readInt();
    string out;
    while (T--) {
        int n = (int)readInt();
        vector<long long> L(n), R(n);
        for (int i = 0; i < n; i++) L[i] = readInt();
        for (int i = 0; i < n; i++) R[i] = readInt();
        for (int k = 0; k < 31; k++) bucket[k].clear();
        C = 0;
        for (int i = 0; i < n; i++) addRange(L[i], R[i]);
        long long ans = -1;
        for (int K = 29; K >= 0; K--) {
            size_t sz = bucket[K].size();
            if (sz >= 2) {
                ans = ((C >> (K + 1)) << (K + 1)) | ((1LL << (K + 1)) - 1);
                break;
            }
            if (sz == 1) {
                long long l = bucket[K][0].first, r = bucket[K][0].second;
                long long low = (1LL << K) - 1;
                long long c = (C >> K) & 1;
                if (c == 0) {
                    C ^= (1LL << K);
                    addRange(0, r & low);
                } else {
                    addRange(l & low, low);
                }
            }
        }
        if (ans < 0) ans = C;
        out += to_string(ans);
        out += '\n';
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}