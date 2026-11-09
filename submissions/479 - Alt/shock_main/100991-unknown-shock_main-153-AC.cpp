
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

typedef long long ll;
typedef long long Val;


static char *inbuf = nullptr;
static size_t inpos = 0, inlen = 0;

static void read_all_input() {
    size_t cap = 1u << 22;
    inbuf = (char *)malloc(cap);
    size_t got;
    while ((got = fread(inbuf + inlen, 1, cap - inlen, stdin)) > 0) {
        inlen += got;
        if (inlen == cap) {
            cap <<= 1;
            inbuf = (char *)realloc(inbuf, cap);
        }
    }
}

static inline ll next_int() {
    while (inpos < inlen && (inbuf[inpos] < '0' || inbuf[inpos] > '9') && inbuf[inpos] != '-')
        ++inpos;
    bool neg = false;
    if (inpos < inlen && inbuf[inpos] == '-') { neg = true; ++inpos; }
    ll x = 0;
    while (inpos < inlen && inbuf[inpos] >= '0' && inbuf[inpos] <= '9')
        x = x * 10 + (inbuf[inpos++] - '0');
    return neg ? -x : x;
}

static std::vector<char> outbuf;

static inline void emit_int(Val v) {
    if (v < 0) { outbuf.push_back('-'); v = -v; }
    char tmp[24];
    int n = 0;
    do { tmp[n++] = char('0' + v % 10); v /= 10; } while (v);
    while (n) outbuf.push_back(tmp[--n]);
}

static inline ll isqrt_ll(ll n) {
    if (n <= 0) return 0;
    ll r = (ll)sqrtl((long double)n);
    while (r > 0 && r * r > n) --r;
    while ((r + 1) * (r + 1) <= n) ++r;
    return r;
}

int main() {
    read_all_input();
    if (inlen == 0) return 0;

    ll num_tests = next_int();
    outbuf.reserve(1u << 22);

    for (ll test = 0; test < num_tests; ++test) {
        ll R = next_int(), C = next_int(), Q = next_int();

        std::vector<ll> qrow(Q), qcol(Q), qpow(Q);
        for (ll i = 0; i < Q; ++i) {
            qrow[i] = next_int();
            qcol[i] = next_int();
            qpow[i] = next_int();
        }

        std::vector<Val> grid((size_t)R * (size_t)C, 0);
        std::vector<std::vector<std::pair<ll, ll>>> intervals(R);
        std::vector<ll> nxt(R + 1);
        for (ll i = 0; i <= R; ++i) nxt[i] = i;
        ll active_rows = R;

        for (ll i = Q - 1; i >= 0 && active_rows > 0; --i) {
            const ll qr = qrow[i], qc = qcol[i], p = qpow[i];
            const ll p2 = p * p;

            const ll r_min = std::max((ll)0, qr - p);
            const ll r_max = std::min(R - 1, qr + p);

            ll r = r_min;
            while (r <= r_max) {
                ll root = r;
                while (nxt[root] != root) root = nxt[root];
                ll cur = r;
                while (nxt[cur] != root) { ll t = nxt[cur]; nxt[cur] = root; cur = t; }
                r = root;
                if (r > r_max) break;

                const ll dr2 = (r - qr) * (r - qr);
                const ll dc_max = isqrt_ll(p2 - dr2);
                const ll c_min = std::max((ll)0, qc - dc_max);
                const ll c_max = std::min(C - 1, qc + dc_max);

                if (c_min <= c_max) {
                    std::vector<std::pair<ll, ll>> &row = intervals[r];
                    const ll n_ints = (ll)row.size();

                    if (n_ints == 1 && row[0].first <= c_min && row[0].second >= c_max) {
                        ++r;
                        continue;
                    }

                    const size_t r_idx = (size_t)r * (size_t)C;
                    const ll base = p2 - dr2 + 1;

                    ll lo = 0, hi = n_ints;
                    const ll target = c_min - 1;
                    while (lo < hi) {
                        ll mid = (lo + hi) >> 1;
                        if (row[mid].second < target) lo = mid + 1;
                        else hi = mid;
                    }
                    const ll first = lo;
                    ll c = c_min, idx = first;
                    while (c <= c_max) {
                        if (idx < n_ints && row[idx].first <= c) {
                            if (row[idx].second >= c) c = row[idx].second + 1;
                            ++idx;
                            continue;
                        }
                        const ll g_end =
                            (idx < n_ints && row[idx].first <= c_max) ? row[idx].first - 1 : c_max;
                        for (ll x = c; x <= g_end; ++x) {
                            const ll d = x - qc;
                            grid[r_idx + (size_t)x] = base - d * d;
                        }
                        c = g_end + 1;
                    }

                    while (idx < n_ints && row[idx].first <= c_max + 1) ++idx;

                    ll m_lo = c_min, m_hi = c_max;
                    if (idx > first) {
                        if (row[first].first < m_lo) m_lo = row[first].first;
                        if (row[idx - 1].second > m_hi) m_hi = row[idx - 1].second;
                        row[first] = std::make_pair(m_lo, m_hi);
                        row.erase(row.begin() + (first + 1), row.begin() + idx);
                    } else {
                        row.insert(row.begin() + first, std::make_pair(m_lo, m_hi));
                    }

                    if (m_lo == 0 && m_hi == C - 1) {
                        nxt[r] = r + 1;
                        --active_rows;
                    }
                }

                ++r;
            }
        }

        for (ll rr = 0; rr < R; ++rr) {
            const size_t s = (size_t)rr * (size_t)C;
            for (ll cc = 0; cc < C; ++cc) {
                if (cc) outbuf.push_back(' ');
                emit_int(grid[s + (size_t)cc]);
            }
            outbuf.push_back('\n');
        }
    }

    fwrite(outbuf.data(), 1, outbuf.size(), stdout);
    return 0;
}
