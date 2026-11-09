#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;

static constexpr int BITS = 30;

struct XorBasis {
    u32 b[BITS]{};

    void add(u32 x) {
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (((x >> bit) & 1U) == 0) continue;
            if (b[bit]) x ^= b[bit];
            else {
                b[bit] = x;
                return;
            }
        }
    }

    u32 getMax(u32 x) const {
        for (int bit = BITS - 1; bit >= 0; --bit) {
            if (b[bit] && (x ^ b[bit]) > x) x ^= b[bit];
        }
        return x;
    }
};

struct ParityBasis {
    XorBasis even;
    bool hasOdd = false;
    u32 oddVector = 0;

    void add(u32 x) {
        if (x & 1U) {
            if (!hasOdd) {
                hasOdd = true;
                oddVector = x;
            } else {
                even.add(x ^ oddVector);
            }
        } else {
            even.add(x);
        }
    }

    // Maximum value in base + span, with bit 0 fixed to target.
    bool getMaxWithParity(u32 base, int target, u32 &answer) const {
        if (hasOdd) {
            if ((int)(base & 1U) != target) base ^= oddVector;
            answer = even.getMax(base);
            return true;
        }

        if ((int)(base & 1U) != target) return false;
        answer = even.getMax(base);
        return true;
    }
};

int highestBit(u32 x) {
    if (x == 0) return -1;
    return 31 - __builtin_clz(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        cin >> N;

        vector<u32> L(N), R(N), D(N);
        u32 baseAllL = 0;

        XorBasis endpointBasis;

        for (int i = 0; i < N; ++i) cin >> L[i];
        for (int i = 0; i < N; ++i) cin >> R[i];

        for (int i = 0; i < N; ++i) {
            D[i] = L[i] ^ R[i];
            baseAllL ^= L[i];
            endpointBasis.add(D[i]);
        }

        // Case 1: choose only interval endpoints.
        u64 answer = endpointBasis.getMax(baseAllL);

        // Try every possible highest bit t where a chosen number
        // first becomes strictly inside its interval.
        for (int t = 0; t < BITS; ++t) {
            vector<u32> d(N);
            vector<int> single, both, none;
            u32 base = 0;

            // Classify each interval for this bit.
            // single: exactly one endpoint can release at bit t.
            // both:   either endpoint can release at bit t.
            // none:   neither endpoint can release at bit t.
            for (int i = 0; i < N; ++i) {
                d[i] = D[i] >> t;
                int diffBit = highestBit(D[i]);
                int lb = (L[i] >> t) & 1U;
                int rb = (R[i] >> t) & 1U;

                bool canUseL = false;
                bool canUseR = false;

                if (t < diffBit) {
                    canUseL = (lb == 0);
                    canUseR = (rb == 1);
                }

                if (canUseL && canUseR) {
                    both.push_back(i);
                    base ^= (L[i] >> t);
                } else if (canUseL) {
                    single.push_back(i);
                    // R is non-eligible; toggling chooses eligible L.
                    base ^= (R[i] >> t);
                } else if (canUseR) {
                    single.push_back(i);
                    // L is non-eligible; toggling chooses eligible R.
                    base ^= (L[i] >> t);
                } else {
                    none.push_back(i);
                    base ^= (L[i] >> t);
                }
            }

            // Build a basis of all endpoint differences d[i].
            // Also compute each d[i]'s coordinates in the selected basis.
            u32 pivot[BITS]{};
            u32 pivotMask[BITS]{};

            vector<u32> basisVector;
            vector<int> basisOriginal;
            vector<char> isBasis(N, false);

            for (int i = 0; i < N; ++i) {
                u32 x = d[i];
                u32 mask = 0;

                for (int bit = BITS - 1; bit >= 0; --bit) {
                    if (((x >> bit) & 1U) == 0) continue;

                    if (pivot[bit]) {
                        x ^= pivot[bit];
                        mask ^= pivotMask[bit];
                    } else {
                        int id = (int)basisVector.size();
                        pivot[bit] = x;
                        pivotMask[bit] = mask ^ (1U << id);

                        basisVector.push_back(d[i]);
                        basisOriginal.push_back(i);
                        isBasis[i] = true;
                        break;
                    }
                }
            }

            int rank = (int)basisVector.size();
            vector<int> basisIndex(N, -1);

            for (int k = 0; k < rank; ++k) {
                basisIndex[basisOriginal[k]] = k;
            }

            vector<u32> coord(N, 0);

            for (int i = 0; i < N; ++i) {
                u32 x = d[i];
                u32 mask = 0;

                for (int bit = BITS - 1; bit >= 0; --bit) {
                    if (((x >> bit) & 1U) == 0) continue;
                    x ^= pivot[bit];
                    mask ^= pivotMask[bit];
                }

                coord[i] = mask;
            }

            vector<int> nonBasis;
            nonBasis.reserve(N - rank);
            vector<int> nonBasisCount(rank, 0);

            for (int i = 0; i < N; ++i) {
                if (!isBasis[i]) {
                    nonBasis.push_back(i);

                    u32 mask = coord[i];
                    while (mask) {
                        int bit = __builtin_ctz(mask);
                        ++nonBasisCount[bit];
                        mask &= mask - 1;
                    }
                }
            }

            XorBasis fullBasis;
            for (u32 x : basisVector) fullBasis.add(x);
            u32 fullMaximum = fullBasis.getMax(base);

            // A: maximum prefix when at least two intervals can release at t.
            bool hasA = false;
            u32 bestA = 0;

            auto updateA = [&](u32 x) {
                if (!hasA || x > bestA) {
                    hasA = true;
                    bestA = x;
                }
            };

            int guaranteed = (int)both.size();
            int sCount = (int)single.size();

            if (guaranteed >= 2) {
                updateA(fullMaximum);
            } else if (guaranteed == 1) {
                bool unrestricted = false;

                for (int i : single) {
                    if (!isBasis[i]) {
                        unrestricted = true;
                        break;
                    }

                    int a = basisIndex[i];
                    if (nonBasisCount[a] > 0) {
                        unrestricted = true;
                        break;
                    }
                }

                if (unrestricted) {
                    updateA(fullMaximum);
                } else {
                    // Each eligible single variable is essential to the basis.
                    for (int i : single) {
                        int a = basisIndex[i];
                        XorBasis h;

                        for (int k = 0; k < rank; ++k) {
                            if (k != a) h.add(basisVector[k]);
                        }

                        updateA(h.getMax(base ^ d[i]));
                    }
                }
            } else {
                vector<int> singleNonBasis, singleBasis;

                for (int i : single) {
                    if (isBasis[i]) singleBasis.push_back(i);
                    else singleNonBasis.push_back(i);
                }

                if ((int)singleNonBasis.size() >= 2) {
                    updateA(fullMaximum);
                } else if ((int)singleNonBasis.size() == 1) {
                    int j = singleNonBasis[0];
                    bool unrestricted = false;

                    for (int i : singleBasis) {
                        int a = basisIndex[i];
                        int used = (coord[j] >> a) & 1U;

                        if (nonBasisCount[a] - (int)used > 0) {
                            unrestricted = true;
                            break;
                        }
                    }

                    if (unrestricted) {
                        updateA(fullMaximum);
                    } else {
                        for (int i : singleBasis) {
                            int a = basisIndex[i];
                            XorBasis h;

                            for (int k = 0; k < rank; ++k) {
                                if (k != a) h.add(basisVector[k]);
                            }

                            updateA(h.getMax(base ^ d[j] ^ basisVector[a]));
                        }
                    }
                } else if ((int)singleBasis.size() >= 2) {
                    // Fix two eligible basis variables. The remaining
                    // non-basis vectors are projected onto these two
                    // coordinates; their possible patterns are 00, 01, 10, 11.
                    int W = (int)nonBasis.size();
                    int words = (W + 63) / 64;

                    vector<vector<u64>> bitsets(rank, vector<u64>(words, 0));

                    for (int k = 0; k < W; ++k) {
                        u32 mask = coord[nonBasis[k]];

                        while (mask) {
                            int bit = __builtin_ctz(mask);
                            bitsets[bit][k >> 6] |= (1ULL << (k & 63));
                            mask &= mask - 1;
                        }
                    }

                    for (int x = 0; x < (int)singleBasis.size(); ++x) {
                        int a = basisIndex[singleBasis[x]];

                        for (int y = x + 1; y < (int)singleBasis.size(); ++y) {
                            int b = basisIndex[singleBasis[y]];

                            bool has10 = false;
                            bool has01 = false;
                            bool has11 = false;

                            for (int w = 0; w < words; ++w) {
                                u64 aa = bitsets[a][w];
                                u64 bb = bitsets[b][w];

                                if (aa & bb) has11 = true;
                                if (aa & ~bb) has10 = true;
                                if (bb & ~aa) has01 = true;

                                if (has10 && has01 && has11) break;
                            }

                            XorBasis h;

                            for (int k = 0; k < rank; ++k) {
                                if (k != a && k != b) h.add(basisVector[k]);
                            }

                            if (has10) h.add(basisVector[a]);
                            if (has01) h.add(basisVector[b]);
                            if (has11) h.add(basisVector[a] ^ basisVector[b]);

                            updateA(h.getMax(base ^ basisVector[a] ^ basisVector[b]));
                        }
                    }
                }
            }

            // B: exactly one interval releases at bit t.
            // Its resulting bit is the endpoint parity XOR 1.
            bool hasB0 = false, hasB1 = false;
            u32 bestB0 = 0, bestB1 = 0;

            auto updateB = [&](int parity, u32 x) {
                if (parity == 0) {
                    if (!hasB0 || x > bestB0) {
                        hasB0 = true;
                        bestB0 = x;
                    }
                } else {
                    if (!hasB1 || x > bestB1) {
                        hasB1 = true;
                        bestB1 = x;
                    }
                }
            };

            if (guaranteed == 1) {
                // The one both-eligible interval is released.
                // All single-eligible intervals must remain non-eligible.
                ParityBasis h;

                for (int i : both) h.add(d[i]);
                for (int i : none) h.add(d[i]);

                u32 candidate;
                if (h.getMaxWithParity(base, 0, candidate)) updateB(0, candidate);
                if (h.getMaxWithParity(base, 1, candidate)) updateB(1, candidate);
            } else if (guaranteed == 0 && sCount > 0) {
                // Exactly one single-eligible interval is released.
                // All no-eligible intervals remain free.
                ParityBasis h;
                for (int i : none) h.add(d[i]);

                for (int target = 0; target <= 1; ++target) {
                    for (int i : single) {
                        u32 candidate;
                        if (h.getMaxWithParity(base ^ d[i], target, candidate)) {
                            updateB(target, candidate);
                        }
                    }
                }
            }

            // Convert the prefix back to the full answer.
            if (hasA) {
                u64 high = (u64)(bestA >> 1);
                u64 candidate = (high << (t + 1)) | ((1ULL << (t + 1)) - 1);
                answer = max(answer, candidate);
            }

            if (hasB0) {
                u64 high = (u64)(bestB0 >> 1);
                u64 candidate = (high << (t + 1)) | ((1ULL << (t + 1)) - 1);
                answer = max(answer, candidate);
            }

            if (hasB1) {
                u64 high = (u64)(bestB1 >> 1);
                u64 candidate = (high << (t + 1)) | ((1ULL << t) - 1);
                answer = max(answer, candidate);
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
