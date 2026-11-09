// Super Ben Galaxy 2 -- C++17 port of the Python v3 solution.
//
// The board is a graph whose states are (cell, mode), mode 0 = blue and
// mode 1 = red.  From a cell you may walk to an orthogonal neighbour that
// is active in your mode, and on a normal ('.') cell you may also flip to
// the other mode.  Every query starts on a '.' cell in blue mode and asks
// whether the target cell (in either mode) is within K steps.
//
// Method (same as v3):
//   1. Compute exact distance fields from a few landmark roots.  A field f
//      bounds every query: |f(s) - f(e)| <= dist(s, e) <= f(s) + f(e),
//      which settles most queries outright.
//   2. Whatever is left is answered by grouped breadth-first searches
//      sharing the rarer side (all starts, or all ends), each capped at
//      the largest K in its group.

#include <bits/stdc++.h>
using namespace std;

const int INF_INT = 1e9;
const long long INF = (long long)1e18;   // must stay above max K (1e9)

// Per-test-case board data shared by every search.
struct Board {
    int n, m, nm;
    vector<char> act[2];     // act[mode][cell]: cell active in that mode
    vector<char> normal;     // '.' cells (active in both, mode flips here)
    vector<vector<int>> adj; // lazily built neighbour lists, state ids
    vector<char> built;
};

// Neighbours of state u, built once and cached (v3 does the same).
// State id = mode * nm + cell.
const vector<int>& neighbours(Board& b, int u) {
    if (b.built[u]) return b.adj[u];
    int nm = b.nm, m = b.m;
    int cell = (u < nm) ? u : u - nm;
    const vector<char>& a = (u < nm) ? b.act[0] : b.act[1];
    int other = (u < nm) ? u + nm : u - nm;
    vector<int> nbrs;
    if (b.normal[cell]) nbrs.push_back(other);
    int c = cell % m;
    if (c > 0 && a[cell - 1]) nbrs.push_back(u - 1);
    if (c + 1 < m && a[cell + 1]) nbrs.push_back(u + 1);
    if (cell >= m && a[cell - m]) nbrs.push_back(u - m);
    if (cell + m < nm && a[cell + m]) nbrs.push_back(u + m);
    b.adj[u] = move(nbrs);
    b.built[u] = 1;
    return b.adj[u];
}

// Flat BFS over the state graph.  If targets is non-empty the search
// stops once every target is reached or the depth exceeds cap.
// Returns {dist, complete}: dist has -1 for unreached states, and
// complete says the frontier ran out (dist is exact on the component).
pair<vector<int>, bool> bfs(Board& b, const vector<int>& sources,
                            const unordered_set<int>* targets,
                            long long cap) {
    int nm = b.nm;
    vector<int> dist(2 * nm, -1);
    vector<int> queue;
    queue.reserve(2 * nm);
    for (int s : sources) {
        if (dist[s] < 0) {
            dist[s] = 0;
            queue.push_back(s);
        }
    }
    long long need = targets ? (long long)targets->size() : 0;
    long long found = 0;
    if (targets) {
        for (int s : sources)
            if (targets->count(s)) ++found;
    }
    size_t head = 0;
    long long depth = 0;
    while (head < queue.size()) {
        if (targets && (found >= need || depth >= cap)) break;
        size_t level_end = queue.size();
        ++depth;
        while (head < level_end) {
            int u = queue[head++];
            for (int v : neighbours(b, u)) {
                if (dist[v] < 0) {
                    dist[v] = (int)depth;
                    queue.push_back(v);
                    if (targets && targets->count(v)) ++found;
                }
            }
        }
    }
    bool complete = head >= queue.size();
    return {move(dist), complete};
}

// Fast input scanner (all tokens are ints or whitespace-free strings).
struct Scanner {
    static const int BUFSIZE = 1 << 20;
    char buf[BUFSIZE];
    int idx, size;
    Scanner() : idx(0), size(0) {}
    inline char getChar() {
        if (idx >= size) {
            size = fread(buf, 1, BUFSIZE, stdin);
            idx = 0;
            if (size == 0) return 0;
        }
        return buf[idx++];
    }
    bool nextInt(int& out) {
        char c;
        int sign = 1;
        int val = 0;
        c = getChar();
        if (!c) return false;
        while (c != '-' && (c < '0' || c > '9')) {
            c = getChar();
            if (!c) return false;
        }
        if (c == '-') { sign = -1; c = getChar(); }
        for (; c >= '0' && c <= '9'; c = getChar())
            val = val * 10 + (c - '0');
        out = val * sign;
        return true;
    }
    bool nextToken(string& out) {
        char c = getChar();
        if (!c) return false;
        while (c == ' ' || c == '\n' || c == '\r' || c == '\t') {
            c = getChar();
            if (!c) return false;
        }
        out.clear();
        while (c != ' ' && c != '\n' && c != '\r' && c != '\t' && c) {
            out.push_back(c);
            c = getChar();
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Scanner sc;
    int t;
    if (!sc.nextInt(t)) return 0;
    string out;
    bool firstLine = true;
    auto emit = [&](const char* s) {
        if (!firstLine) out.push_back('\n');
        firstLine = false;
        out += s;
    };

    for (int tc = 0; tc < t; ++tc) {
        int n, m, q;
        sc.nextInt(n); sc.nextInt(m); sc.nextInt(q);
        vector<string> grid(n);
        for (int r = 0; r < n; ++r) sc.nextToken(grid[r]);
        struct Query { int sc_, ec, k; };
        vector<Query> queries(q);
        for (int i = 0; i < q; ++i) {
            int rs, cs, re, ce, k;
            sc.nextInt(rs); sc.nextInt(cs); sc.nextInt(re); sc.nextInt(ce);
            sc.nextInt(k);
            queries[i] = {rs * m + cs, re * m + ce, k};
        }
        int nm = n * m;

        Board b;
        b.n = n; b.m = m; b.nm = nm;
        b.act[0].assign(nm, 0);
        b.act[1].assign(nm, 0);
        b.normal.assign(nm, 0);
        for (int r = 0; r < n; ++r) {
            const string& row = grid[r];
            int base = r * m;
            for (int c = 0; c < m; ++c) {
                char ch = row[c];
                int cell = base + c;
                if (ch == '.') {
                    b.act[0][cell] = 1;
                    b.act[1][cell] = 1;
                    b.normal[cell] = 1;
                } else if (ch == 'B') {
                    b.act[0][cell] = 1;
                } else { // 'R'
                    b.act[1][cell] = 1;
                }
            }
        }
        b.adj.assign(2 * nm, {});
        b.built.assign(2 * nm, 0);

        const int UNSET = 0, YES = 1, NO = 2;
        vector<int> ans(q, UNSET);
        vector<int> s_state(q, 0), e_blue(q, -1), e_red(q, -1), kval(q, 0);
        vector<int> undecided;
        for (int i = 0; i < q; ++i) {
            kval[i] = queries[i].k;
            s_state[i] = queries[i].sc_;          // starts are '.' -> blue
            int ec = queries[i].ec;
            if (b.act[0][ec]) e_blue[i] = ec;
            if (b.act[1][ec]) e_red[i] = nm + ec;
            if (queries[i].sc_ == ec) ans[i] = YES;  // distance 0 <= K
            else undecided.push_back(i);
        }

        // ---- landmark distance bounds --------------------------------
        vector<long long> ub(q, INF);
        vector<int> lbm0(q, 0), lbm1(q, 0), seen(q, 0), dead(q, 0);

        function<void(const vector<int>&)> apply_field =
            [&](const vector<int>& f) {
            vector<int> still;
            still.reserve(undecided.size());
            for (int i : undecided) {
                int ds = f[s_state[i]];
                int dd = dead[i];
                int sn = seen[i];
                long long best_lb = INF;
                int eb = e_blue[i];
                if (eb >= 0 && !(dd & 1)) {
                    int de = f[eb];
                    if (ds >= 0 && de >= 0) {
                        if ((long long)ds + de < ub[i]) ub[i] = (long long)ds + de;
                        int d = abs(ds - de);
                        if (d > lbm0[i]) lbm0[i] = d;
                        sn |= 1;
                    } else if ((ds >= 0) != (de >= 0)) {
                        dd |= 1;
                    }
                    if (sn & 1) best_lb = min(best_lb, (long long)lbm0[i]);
                    else best_lb = 0;
                }
                int er = e_red[i];
                if (er >= 0 && !(dd & 2)) {
                    int de = f[er];
                    if (ds >= 0 && de >= 0) {
                        if ((long long)ds + de < ub[i]) ub[i] = (long long)ds + de;
                        int d = abs(ds - de);
                        if (d > lbm1[i]) lbm1[i] = d;
                        sn |= 2;
                    } else if ((ds >= 0) != (de >= 0)) {
                        dd |= 2;
                    }
                    if (sn & 2) best_lb = min(best_lb, (long long)lbm1[i]);
                    else best_lb = 0;
                }
                dead[i] = dd;
                seen[i] = sn;
                bool live = (eb >= 0 && !(dd & 1)) || (er >= 0 && !(dd & 2));
                if (!live) ans[i] = NO;
                else if (ub[i] <= kval[i]) ans[i] = YES;
                else if (best_lb > kval[i]) ans[i] = NO;
                else still.push_back(i);
            }
            undecided = move(still);
        };

        if (q > 8 && !undecided.empty()) {
            unordered_map<int, int> freq;
            vector<int> firstSeen;
            auto bump = [&](int s) {
                auto it = freq.find(s);
                if (it == freq.end()) {
                    freq[s] = 1;
                    firstSeen.push_back(s);
                } else {
                    ++it->second;
                }
            };
            for (int i = 0; i < q; ++i) {
                bump(s_state[i]);
                if (e_blue[i] >= 0) bump(e_blue[i]);
                if (e_red[i] >= 0) bump(e_red[i]);
            }
            vector<int> cand = firstSeen;
            stable_sort(cand.begin(), cand.end(), [&](int a, int c) {
                return freq[a] > freq[c];
            });
            size_t candCap = (nm <= 2000) ? 300 : 1500;
            if (cand.size() > candCap) cand.resize(candCap);
            int maxLandmarks = (nm <= 2000) ? 5 : 8;
            vector<vector<int>> fields;
            while (!undecided.empty() && (int)fields.size() < maxLandmarks) {
                if ((int)fields.size() >= 2 && undecided.size() <= 6) break;
                int root;
                if (fields.empty()) {
                    root = cand[0];
                } else {
                    root = -1;
                    long long best_d = -1;
                    for (int s : cand) {
                        long long dmin = INF;
                        for (auto& f : fields) {
                            int d = f[s];
                            if (d < 0) { dmin = INF; break; }
                            if (d < dmin) dmin = d;
                        }
                        if (dmin > best_d) {
                            best_d = dmin;
                            root = s;
                        }
                    }
                    if (root < 0 || best_d <= 2) break;
                }
                auto res = bfs(b, vector<int>{root}, nullptr, INF);
                fields.push_back(move(res.first));
                apply_field(fields.back());
            }
        }

        // ---- residue: grouped BFS on the rarer side -------------------
        if (!undecided.empty()) {
            unordered_map<int, vector<int>> by_start, by_end;
            vector<int> startOrder, endOrder;
            for (int i : undecided) {
                auto it = by_start.find(s_state[i]);
                if (it == by_start.end()) {
                    by_start[s_state[i]] = {i};
                    startOrder.push_back(s_state[i]);
                } else it->second.push_back(i);
                int ec = queries[i].ec;
                auto jt = by_end.find(ec);
                if (jt == by_end.end()) {
                    by_end[ec] = {i};
                    endOrder.push_back(ec);
                } else jt->second.push_back(i);
            }
            bool use_start = by_start.size() <= by_end.size();
            vector<int> order = use_start ? startOrder : endOrder;
            auto& groups = use_start ? by_start : by_end;
            stable_sort(order.begin(), order.end(), [&](int a, int c) {
                return groups[a].size() > groups[c].size();
            });
            int checks = 0;
            for (int anchor : order) {
                vector<int> members;
                for (int i : groups[anchor])
                    if (ans[i] == UNSET) members.push_back(i);
                if (members.empty()) continue;
                long long cap = 0;
                for (int i : members) cap = max(cap, (long long)kval[i]);
                vector<int> sources;
                unordered_set<int> targets;
                if (use_start) {
                    sources = {anchor};
                    for (int i : members) {
                        if (e_blue[i] >= 0) targets.insert(e_blue[i]);
                        if (e_red[i] >= 0) targets.insert(e_red[i]);
                    }
                } else {
                    if (b.act[0][anchor]) sources.push_back(anchor);
                    if (b.act[1][anchor]) sources.push_back(nm + anchor);
                    for (int i : members) targets.insert(s_state[i]);
                }
                auto res = bfs(b, sources, &targets, cap);
                const vector<int>& f = res.first;
                bool complete = res.second;
                if (use_start) {
                    for (int i : members) {
                        long long d = INF;
                        if (e_blue[i] >= 0 && f[e_blue[i]] >= 0)
                            d = f[e_blue[i]];
                        if (e_red[i] >= 0 && f[e_red[i]] >= 0 && f[e_red[i]] < d)
                            d = f[e_red[i]];
                        ans[i] = (d <= kval[i]) ? YES : NO;
                    }
                } else {
                    for (int i : members) {
                        int d = f[s_state[i]];
                        ans[i] = (0 <= d && d <= kval[i]) ? YES : NO;
                    }
                }
                if (complete) {
                    // an exhausted search is an exact field: reuse it
                    vector<int> rest;
                    for (int i : undecided)
                        if (ans[i] == UNSET) rest.push_back(i);
                    undecided = move(rest);
                    if (!undecided.empty()) {
                        ++checks;
                        if (checks <= 10 || checks % 5 == 0)
                            apply_field(f);
                    }
                }
            }
        }

        for (int i = 0; i < q; ++i)
            emit(ans[i] == YES ? "YES" : "NO");
    }

    fwrite(out.c_str(), 1, out.size(), stdout);
    return 0;
}
