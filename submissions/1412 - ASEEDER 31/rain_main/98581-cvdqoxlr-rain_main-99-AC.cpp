#include<bits/stdc++.h>
using namespace std;
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
        if (ipos >= ilen) { if (eofReached) return 0; fill(); continue; }
        char c = ibuf[ipos];
        if (c >= '0' && c <= '9') break;
        ++ipos;
    }
    long long x = 0;
    while (true) {
        if (ipos >= ilen) { if (eofReached) break; fill(); continue; }
        char c = ibuf[ipos];
        if (c < '0' || c > '9') break;
        x = x * 10 + (c - '0');
        ++ipos;
    }
    return x;
}

static inline char readDir() {
    while (true) {
        if (ipos >= ilen) { if (eofReached) return 0; fill(); continue; }
        char c = ibuf[ipos];
        if (c == ' ' || c == '\n' || c == '\r' || c == '\t') { ++ipos; continue; }
        ++ipos;
        return c;
    }
}

// bucket width: bigger than any x coordinate (0 <= x <= 1e5)
static const long long BUCKET = 1 << 17;

int main() {
    int T = (int)readInt();

    vector<long long> nKeys;                 // (x + y) * BUCKET + x  for every N(orth) drone
    vector<pair<long long, int>> eList;      // (x + y, x)            for every E(ast) drone
    string out;
    out.reserve(1 << 12);

    while (T--) {
        int n = (int)readInt();
        long long K = readInt();

        nKeys.clear();
        eList.clear();
        nKeys.reserve(n);
        eList.reserve(n);

        for (int i = 0; i < n; ++i) {
            long long x = readInt();
            long long y = readInt();
            (void)readInt();                 // z is irrelevant: within one cell the higher one wins
            char dir = readDir();
            long long c = x + y;
            if (dir == 'E') eList.push_back({c, (int)x});
            else            nKeys.push_back(c * BUCKET + x);
        }

        sort(nKeys.begin(), nKeys.end());

        long long meetings = 0;
        for (size_t i = 0; i < eList.size(); ++i) {
            long long c = eList[i].first;
            long long xe = eList[i].second;
            // an East drone at (xe + s, ye) and a North drone at (xn, yn + s) meet iff
            //   s = xn - xe = ye - yn, i.e. same diagonal (x+y) and 0 <= xn - xe <= K-1
            long long loKey = c * BUCKET + xe;
            long long hiX = xe + K - 1;
            if (hiX > BUCKET - 1) hiX = BUCKET - 1;
            long long hiKey = c * BUCKET + hiX;
            meetings += upper_bound(nKeys.begin(), nKeys.end(), hiKey)
                      - lower_bound(nKeys.begin(), nKeys.end(), loKey);
        }

        out += to_string((long long)n * K - meetings);
        out.push_back('\n');
    }

    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
