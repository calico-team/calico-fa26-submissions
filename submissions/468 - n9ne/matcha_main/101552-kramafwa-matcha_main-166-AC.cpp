#include <iostream>
#include <vector>
using namespace std;

const int B = 30;

int solve(int N, vector<int> L, vector<int> R) {
    int base = 0;
    vector<int> D(N), top(N, -1), nz;
    for (int i = 0; i < N; i++) {
        base ^= L[i];
        D[i] = L[i] ^ R[i];
        if (D[i]) {
            top[i] = 31 - __builtin_clz(D[i]);
            nz.push_back(i);
        }
    }

    auto sides = [&](int i, int b) {
        int sl = (~L[i] >> b) & 1;
        int sr = (R[i] >> b) & 1;
        return sl | (sr << 1);
    };

    vector<unsigned> depMasks;
    int P = 0;
    for (int b = B - 1; b >= 0; b--) {
        int w = B - b;
        int tb[B] = {};
        unsigned tm[B] = {};
        int ids[B];
        int cnt = 0;
        unsigned ones = 0, twos = 0;
        int depElig = 0, dsides = 0;
        unsigned dm = 0;
        depMasks.clear();

        for (int i : nz) {
            if (top[i] < b) continue;
            int x = D[i] >> b;
            unsigned m = 0;
            bool placed = false;
            for (int k = w - 1; k >= 0; k--) {
                if (!((x >> k) & 1)) continue;
                if (tb[k]) {
                    x ^= tb[k];
                    m ^= tm[k];
                } else {
                    tb[k] = x;
                    tm[k] = m ^ (1u << cnt);
                    ids[cnt++] = i;
                    placed = true;
                    break;
                }
            }
            if (placed) continue;
            twos |= ones & m;
            ones |= m;
            depMasks.push_back(m);
            if (top[i] > b) {
                int s = sides(i, b);
                if (s && ++depElig == 1) {
                    dm = m;
                    dsides = s;
                }
            }
        }

        int es[B];
        for (int c = 0; c < cnt; c++)
            es[c] = top[ids[c]] > b ? sides(ids[c], b) : 0;

        auto reduce = [&](int T, unsigned& Y) {
            int y = T ^ (base >> b);
            Y = 0;
            for (int k = w - 1; k >= 0; k--) {
                if (!((y >> k) & 1)) continue;
                if (!tb[k]) return false;
                y ^= tb[k];
                Y ^= tm[k];
            }
            return true;
        };

        int done = (P << (b + 1)) | ((2 << b) - 1);

        unsigned Y0, Y1;
        if (reduce(2 * P, Y0)) {
            bool dev = depElig > 0;
            for (int c = 0; c < cnt && !dev; c++)
                for (int s = 0; s < 2; s++)
                    if (((es[c] >> s) & 1) && ((int)((Y0 >> c) & 1) == s || ((ones >> c) & 1)))
                        dev = true;
            if (dev) return done;
        }

        bool ok1 = reduce(2 * P + 1, Y1);
        if (ok1) {
            bool dev = depElig >= 2;

            if (!dev && depElig == 1) {
                for (int c = 0; c < cnt && !dev; c++) {
                    if (!es[c]) continue;
                    int carrier = (dm >> c) & 1;
                    bool others = ((twos >> c) & 1) || (((ones >> c) & 1) && !carrier);
                    for (int s1 = 0; s1 < 2 && !dev; s1++) {
                        if (!((es[c] >> s1) & 1)) continue;
                        for (int s2 = 0; s2 < 2; s2++) {
                            if (!((dsides >> s2) & 1)) continue;
                            if (others || ((int)((Y1 >> c) & 1) ^ (s2 & carrier)) == s1) {
                                dev = true;
                                break;
                            }
                        }
                    }
                }
            }

            if (!dev) {
                int elig = 0;
                for (int c = 0; c < cnt; c++) if (es[c]) elig++;
                if (elig >= 2) {
                    unsigned mb[B] = {};
                    vector<unsigned> vecs;
                    for (unsigned m : depMasks) {
                        unsigned x = m;
                        while (x) {
                            int h = 31 - __builtin_clz(x);
                            if (mb[h]) x ^= mb[h];
                            else { mb[h] = x; vecs.push_back(x); break; }
                        }
                    }
                    unsigned phi[B] = {};
                    for (int c = 0; c < cnt; c++)
                        for (size_t q = 0; q < vecs.size(); q++)
                            if ((vecs[q] >> c) & 1) phi[c] |= 1u << q;
                    for (int c1 = 0; c1 < cnt && !dev; c1++) {
                        if (!es[c1]) continue;
                        for (int c2 = c1 + 1; c2 < cnt && !dev; c2++) {
                            if (!es[c2]) continue;
                            for (int s1 = 0; s1 < 2 && !dev; s1++) {
                                if (!((es[c1] >> s1) & 1)) continue;
                                for (int s2 = 0; s2 < 2; s2++) {
                                    if (!((es[c2] >> s2) & 1)) continue;
                                    int a = (int)((Y1 >> c1) & 1) ^ s1;
                                    int bb = (int)((Y1 >> c2) & 1) ^ s2;
                                    bool ok = (phi[c1] || !a) && (phi[c2] || !bb)
                                              && (phi[c1] != phi[c2] || a == bb);
                                    if (ok) { dev = true; break; }
                                }
                            }
                        }
                    }
                }
            }
            if (dev) return done;
        }
        P = 2 * P + (ok1 ? 1 : 0);
    }
    return P;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        vector<int> L(N), R(N);
        for (int& i : L) cin >> i;
        for (int& i : R) cin >> i;
        cout << solve(N, L, R) << '\n';
    }
    return 0;
}
