
#include <bits/stdc++.h>
using namespace std;

using u64 = unsigned long long;

const int BITS = 30;

// Top bit where l and r differ (-1 if equal).
int highestDiffBit(u64 l, u64 r) {
    u64 d = l ^ r;
    return d ? 63 - __builtin_clzll(d) : -1;
}

// Best XOR using only L[i] or R[i].
u64 bestEndpointXor(const vector<u64>& L, const vector<u64>& R) {
    u64 base = 0;
    u64 basis[BITS + 1] = {};
    for (size_t i = 0; i < L.size(); i++) {
        base ^= L[i];
        u64 d = L[i] ^ R[i];
        for (int b = BITS; b >= 0 && d; b--) {
            if (!(d >> b & 1)) continue;
            if (!basis[b]) { basis[b] = d; d = 0; }
            else d ^= basis[b];
        }
    }
    for (int b = BITS; b >= 0; b--)
        if (basis[b] && !(base >> b & 1)) base ^= basis[b];
    return base;
}

// Can an interval go free at this bit?
enum Kind {
    NEVER,      // no
    ALWAYS,     // yes, from either end
    ONE_SIDED   // yes, from one end only
};

struct Coord {
    Kind kind;
    int  freeSide;    // 0 = from L, 1 = from R
    int  basisIndex;  // -1 if not in basis
    u64  rep;         // basis vectors that make it
};

// XOR basis that remembers what each vector is made of.
struct TrackedBasis {
    u64  vec[64]  = {};
    u64  mask[64] = {};
    bool has[64]  = {};
    int  size     = 0;

    // Add x. Returns its index, or -1 if already covered.
    int insert(u64 x, u64& rep) {
        u64 m = 0;
        for (int b = 63; b >= 0 && x; b--) {
            if (!(x >> b & 1)) continue;
            if (has[b]) { x ^= vec[b]; m ^= mask[b]; continue; }
            has[b] = true; vec[b] = x; mask[b] = m ^ (1ULL << size);
            return size++;
        }
        rep = m;
        return -1;
    }

    // Build x from the basis. False if impossible.
    bool express(u64 x, u64& combo) const {
        combo = 0;
        for (int b = 63; b >= 0 && x; b--) {
            if (!(x >> b & 1)) continue;
            if (!has[b]) return false;
            x ^= vec[b]; combo ^= mask[b];
        }
        return true;
    }
};

// Small XOR basis, just counts rank.
struct SmallSpan {
    u64 basis[64] = {};
    int rank = 0;
    void add(u64 g) {
        for (int b = 63; b >= 0 && g; b--) {
            if (!(g >> b & 1)) continue;
            if (basis[b]) g ^= basis[b];
            else { basis[b] = g; rank++; return; }
        }
    }
    u64 anyVector() const {
        for (int b = 0; b < 64; b++) if (basis[b]) return basis[b];
        return 0;
    }
};

// Can we hit target with at least `need` intervals able to go free?
bool canReach(const vector<Coord>& coords, const TrackedBasis& basis,
              u64 target, int need) {
    u64 combo;
    if (!basis.express(target, combo)) return false;

    // Non-basis ones can be set freely.
    int always = 0, freeOneSided = 0;
    for (const Coord& c : coords) {
        if (c.kind == ALWAYS) always++;
        else if (c.kind == ONE_SIDED && c.basisIndex < 0) freeOneSided++;
    }
    if (always + freeOneSided >= need) return true;

    // Few cases left. A bit in `hits` means that one can go free.
    const int EXTRA = 40;
    int stillNeed = need - always;
    u64 oneSidedBasis = 0, hits = 0;
    for (const Coord& c : coords) {
        if (c.kind != ONE_SIDED) continue;
        if (c.basisIndex >= 0) {
            oneSidedBasis |= 1ULL << c.basisIndex;
            int value = combo >> c.basisIndex & 1;
            if (value == c.freeSide) hits |= 1ULL << c.basisIndex;
        } else if (c.freeSide == 0) {
            hits |= 1ULL << EXTRA;
        }
    }

    // What flipping each free choice changes.
    SmallSpan span;
    for (const Coord& c : coords) {
        if (c.basisIndex >= 0) continue;
        u64 g = c.rep & oneSidedBasis;
        if (c.kind == ONE_SIDED) g |= 1ULL << EXTRA;
        span.add(g);
        // Rank 2 always gives enough.
        if (span.rank >= 2) return true;
    }

    if (__builtin_popcountll(hits) >= stillNeed) return true;
    if (span.rank == 1 && __builtin_popcountll(hits ^ span.anyVector()) >= stillNeed)
        return true;
    return false;
}

// Can some interval go free at bit j?
bool goesFreeAt(int j, const vector<u64>& L, const vector<u64>& R,
                const vector<int>& diffBit, u64 xorL, u64 T0) {
    int n = L.size();
    vector<Coord> coords;
    TrackedBasis basis;
    bool anyCandidate = false;

    for (int i = 0; i < n; i++) {
        if (diffBit[i] < j) continue;  // fixed here

        Coord c{NEVER, 0, -1, 0};
        if (diffBit[i] > j) {
            anyCandidate = true;
            bool fromL = !(L[i] >> j & 1);
            bool fromR =  (R[i] >> j & 1);
            if (fromL && fromR)    c.kind = ALWAYS;
            else if (fromL)        { c.kind = ONE_SIDED; c.freeSide = 0; }
            else if (fromR)        { c.kind = ONE_SIDED; c.freeSide = 1; }
        }
        c.basisIndex = basis.insert((L[i] ^ R[i]) >> j, c.rep);
        coords.push_back(c);
    }
    if (!anyCandidate) return false;

    // T0's top bits, then bit j = 1.
    u64 target = (((T0 >> (j + 1)) << 1) | 1) ^ (xorL >> j);

    // One goes free, or two.
    return canReach(coords, basis, target ^ 1, 1) ||
           canReach(coords, basis, target,     2);
}

u64 solve(const vector<u64>& L, const vector<u64>& R) {
    int n = L.size();
    u64 T0 = bestEndpointXor(L, R);

    u64 xorL = 0;
    vector<int> diffBit(n);
    for (int i = 0; i < n; i++) {
        xorL ^= L[i];
        diffBit[i] = highestDiffBit(L[i], R[i]);
    }

    for (int j = BITS - 1; j >= 0; j--)
        if (goesFreeAt(j, L, R, diffBit, xorL, T0))
            return T0 | ((1ULL << (j + 1)) - 1);
    return T0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<u64> L(n), R(n);
        for (auto& x : L) cin >> x;
        for (auto& x : R) cin >> x;
        cout << solve(L, R) << '\n';
    }
}