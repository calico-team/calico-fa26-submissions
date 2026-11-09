#include <bits/stdc++.h>
using namespace std;

// ---------------------------- streaming input ----------------------------
static char ibuf[1 << 20];
static int ipos = 0, ilen = 0;
static bool eofReached = false;

static inline void fill() {
    ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
    ipos = 0;
    if (ilen <= 0) eofReached = true;
}

static inline long long readInt() {
    while (true) {
        if (ipos >= ilen) {
            if (eofReached) return 0;
            fill();
            continue;
        }
        if (ibuf[ipos] >= '0' && ibuf[ipos] <= '9') break;
        ++ipos;
    }
    long long x = 0;
    while (true) {
        if (ipos >= ilen) {
            if (eofReached) break;
            fill();
            continue;
        }
        char c = ibuf[ipos];
        if (c < '0' || c > '9') break;
        x = x * 10 + (c - '0');
        ++ipos;
    }
    return x;
}

// Omen holds at most 2 charges, so at most 2 recharges are ever in flight.
// f0 = finish time of the first one in line, f1 = that of the second.
struct Smoke {
    int len;         // 0, 1 or 2 recharges pending
    long long f0, f1;
    int charges;     // charges currently in hand

    void init() { len = 0; f0 = f1 = 0; charges = 2; }

    bool hasPending() const { return len > 0; }
    long long firstFinish() const { return f0; }
    long long lastFinish() const { return len == 2 ? f1 : f0; }

    void completeOne() {                       // earliest charge arrives
        if (len == 2) { f0 = f1; len = 1; }
        else len = 0;
        ++charges;
    }

    void startRecharge(long long finish) {     // queue behind the pending ones
        if (len == 0) { f0 = finish; len = 1; }
        else { f1 = finish; len = 2; }
    }
};

static Smoke sm;
static vector<long long> A;

static bool feasible(int n, long long R) {
    sm.init();
    for (int i = 0; i < n; ++i) {
        long long a = A[i];

        // recharges are resolved before the request at the same timestamp
        while (sm.hasPending() && sm.firstFinish() <= a) sm.completeOne();

        if (sm.charges == 0) return false;     // no charge -> cannot smoke

        --sm.charges;
        // a used charge recharges only after the previous recharge finishes
        long long finish = (sm.hasPending() ? sm.lastFinish() : a) + R;
        sm.startRecharge(finish);
    }
    return true;
}

int main() {
    int T = (int)readInt();
    string out;
    out.reserve(1 << 16);

    while (T--) {
        int n = (int)readInt();
        long long R = readInt();
        A.resize(n);
        for (int i = 0; i < n; ++i) A[i] = readInt();

        out += feasible(n, R) ? "YES\n" : "NO\n";
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
