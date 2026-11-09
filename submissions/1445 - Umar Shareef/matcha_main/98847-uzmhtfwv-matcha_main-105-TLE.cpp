// A Matcha a Day -- maximum XOR choosing one value from each interval.
//
// The answer is built one bit at a time, from the most significant bit
// (bit 29) down.  At each bit we split the intervals into:
//   * fixed ones, whose top bit is already decided (both ends share it), and
//   * flexible ones, which straddle the bit boundary and may go either way.
// The fixed intervals contribute a known parity to this bit.  To make the
// answer's bit 1 we need the flexible intervals to have the opposite parity,
// so we try a handful of candidate assignments for them (flip none, flip
// one, flip a pair, flip all -- with only representative interval types
// when there are very many) and keep the best result from the lower bits.
//
// A memo table caches small subproblems.  It is rebuilt for every test case
// and dropped afterwards, and it is hard-capped: a table shared across cases
// grows by megabytes per case on files with many medium cases and the
// process runs out of memory.

#include <bits/stdc++.h>
using namespace std;

using Interval = pair<int, int>;  // one day's choice range [l, r]

// When a level has very many distinct flexible interval types, trying every
// possible "which interval flips" choice is too slow.  In that case we only
// branch over a set of representative types (plus the all-0 / all-1 choices).
const int BRANCH_LIMIT = 48;

// Hard cap on the per-test-case memo table (see the note at the top).
const int CACHE_LIMIT = 20000;

// Memo key: the bit level followed by the flattened interval list.
using MemoKey = vector<int>;
struct MemoKeyHash {
    size_t operator()(MemoKey const& key) const noexcept {
        size_t h = key.size();
        for (int x : key) {
            size_t v = std::hash<int>{}(x);
            h ^= v + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
        }
        return h;
    }
};
using Memo = unordered_map<MemoKey, int, MemoKeyHash>;

int maxXor(const vector<Interval>& intervals, int b, Memo& cache);

// All candidate reduced-interval lists for the flexible intervals,
// restricted to assignments whose bit-b parity equals `need`.
// In every flex interval, bit b itself is still free: l < 2^b <= r.
vector<vector<Interval>> candidates(const vector<Interval>& flex, int b,
                                    int need) {
    int lowFull = (1 << b) - 1;
    int nf = (int)flex.size();

    // Choosing bit b = 0 keeps [l, 2^b - 1]; choosing bit b = 1 keeps
    // [0, r - 2^b].  Only the part below bit b survives either way.
    vector<Interval> red0(nf), red1(nf);
    for (int i = 0; i < nf; i++) {
        red0[i] = {flex[i].first, lowFull};
        red1[i] = {0, flex[i].second - (1 << b)};
    }

    // Group identical interval types, keeping first-occurrence order.
    vector<Interval> typeList;
    vector<vector<int>> typeIdx;
    map<Interval, int> typePos;
    for (int i = 0; i < nf; i++) {
        auto it = typePos.find(flex[i]);
        if (it == typePos.end()) {
            typePos[flex[i]] = (int)typeList.size();
            typeList.push_back(flex[i]);
            typeIdx.push_back({i});
        } else {
            typeIdx[it->second].push_back(i);
        }
    }

    vector<vector<Interval>> out;
    set<vector<int>> seen;

    // Emit the candidate where exactly the intervals in `ones` take bit 1.
    // Identical choices are only emitted once.
    auto emit = [&](vector<int> ones) {
        sort(ones.begin(), ones.end());
        if (!seen.insert(ones).second) return;
        vector<char> isOne(nf, 0);
        for (int i : ones) isOne[i] = 1;
        vector<Interval> cand(nf);
        for (int i = 0; i < nf; i++) cand[i] = isOne[i] ? red1[i] : red0[i];
        out.push_back(move(cand));
    };

    // Types ordered by how much room bit 1 leaves, most room first.
    auto byRoom = [&](const Interval& x, const Interval& y) {
        int rx = x.second - (1 << b);
        int ry = y.second - (1 << b);
        if (rx != ry) return rx > ry;
        return x.first < y.first;
    };

    // Flip nothing (parity 0).
    if (need == 0) emit({});

    // Flip a single interval (parity 1).
    if (need == 1) {
        vector<Interval> reps = typeList;
        int limit = (nf <= 20000 ? BRANCH_LIMIT : 10);
        if ((int)reps.size() > limit) {
            sort(reps.begin(), reps.end(), byRoom);
            reps.resize(limit);
        }
        for (const Interval& lr : reps) emit({typeIdx[typePos[lr]][0]});
    }

    // Flip a pair of intervals (parity 0).
    if (need == 0 && nf >= 2) {
        vector<Interval> reps = typeList;
        if ((int)reps.size() > 6) {
            sort(reps.begin(), reps.end(), byRoom);
            reps.resize(6);
        }
        for (int a = 0; a < (int)reps.size(); a++) {
            for (int c = a; c < (int)reps.size(); c++) {
                int ia = typePos[reps[a]];
                int ic = typePos[reps[c]];
                if (reps[a] == reps[c]) {
                    if ((int)typeIdx[ia].size() >= 2)
                        emit({typeIdx[ia][0], typeIdx[ia][1]});
                } else {
                    emit({typeIdx[ia][0], typeIdx[ic][0]});
                }
            }
        }
    }

    // Flip everything (parity = nf mod 2).
    if (nf % 2 == need && nf > 2) {
        vector<int> all(nf);
        iota(all.begin(), all.end(), 0);
        emit(all);
    }

    return out;
}

int compute(const vector<Interval>& intervals, int b, Memo& cache) {
    int full = (1 << (b + 1)) - 1;
    if ((int)intervals.size() == 1) return intervals[0].second;

    int mask = (1 << b) - 1;
    vector<Interval> fixed, flex;
    int parity = 0;
    for (const Interval& lr : intervals) {
        int l = lr.first, r = lr.second;
        if (l == 0 && r == full) return full;  // a free day absorbs anything
        int hb = l >> b;
        if (hb == (r >> b)) {
            parity ^= hb & 1;
            fixed.push_back({l & mask, r & mask});
        } else {
            flex.push_back({l, r});
        }
    }

    if (flex.empty()) return (parity << b) | maxXor(fixed, b - 1, cache);

    int need = 1 ^ parity;  // flex parity that makes answer bit b equal 1
    int best = -1;
    for (const vector<Interval>& cand : candidates(flex, b, need)) {
        vector<Interval> next = fixed;
        next.insert(next.end(), cand.begin(), cand.end());
        int val = (1 << b) | maxXor(next, b - 1, cache);
        if (val > best) {
            best = val;
            if (best == full) return full;
        }
    }
    return best;
}

// Maximum XOR of one choice per interval, using only bits <= b.
int maxXor(const vector<Interval>& intervals, int b, Memo& cache) {
    if (b < 0 || intervals.empty()) return 0;
    if (intervals.size() <= 64 && (int)cache.size() < CACHE_LIMIT) {
        MemoKey key;
        key.reserve(1 + 2 * intervals.size());
        key.push_back(b);
        for (const Interval& lr : intervals) {
            key.push_back(lr.first);
            key.push_back(lr.second);
        }
        auto it = cache.find(key);
        if (it != cache.end()) return it->second;
        int val = compute(intervals, b, cache);
        cache[key] = val;
        return val;
    }
    return compute(intervals, b, cache);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    string out;
    for (int tc = 0; tc < t; tc++) {
        int n;
        cin >> n;
        vector<int> L(n), R(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        for (int i = 0; i < n; i++) cin >> R[i];
        vector<Interval> intervals(n);
        for (int i = 0; i < n; i++) intervals[i] = {L[i], R[i]};

        Memo cache;  // fresh memo for this case only; freed when it ends
        out += to_string(maxXor(intervals, 29, cache));
        out += '\n';
    }
    cout << out;
    return 0;
}
