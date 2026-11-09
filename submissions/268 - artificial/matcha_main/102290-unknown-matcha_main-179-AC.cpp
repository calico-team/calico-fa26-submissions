#include <iostream>
#include <vector>
using namespace std;

/**
 * Return the maximum possible value of X, Big Ben's matcha enjoyment.
 *
 * N: the days in Big Ben's life
 * L: the lower bound of enjoyment from each store
 * R: the upper bound of enjoyment from each store
 */ 


struct Recipe { unsigned parity; bool toggle; int count; };
static constexpr Recipe recipes[] = {{1, true, 1}, {0, true, 2}, {0, false, 1}};

bool compatible(bool same_form, int a, int b) {
    return (159u >> ((unsigned(same_form) << 2) | (a << 1) | b)) & 1u;
}

bool covers_block(unsigned lo, unsigned hi, unsigned prefix, int bit) {
    const unsigned width = 1u << bit;
    const unsigned scaled = prefix << bit;
    return lo <= 0LL + 1LL * scaled && 0LL + 1LL * scaled + 1LL * width - 1LL * 1 <= hi;
}

struct XorBasis {
    unsigned vector[30]{};
    unsigned source[30]{};

    unsigned reduce(unsigned& value) const {
        unsigned mask = 0;
        while (value != 0) {
            const int bit = 31 - __builtin_clz(value);
            if (vector[bit] == 0) break;
            value ^= vector[bit];
            mask ^= source[bit];
        }
        return mask;
    }

    bool add(unsigned value) {
        const unsigned mask = reduce(value);
        if (value == 0) return false;
        const int bit = 31 - __builtin_clz(value);
        vector[bit] = value;
        source[bit] = mask ^ (1u << bit);
        return true;
    }

    unsigned maximize(unsigned value) const {
        for (int bit = 29; bit >= 0; --bit) {
            if ((value ^ vector[bit]) > value) value ^= vector[bit];
        }
        return value;
    }
};

struct Literal {
    int interval;
    int side;
};


struct PrefixSystem {
    XorBasis basis;
    vector<unsigned> representation;
    vector<int> pivot;
    unsigned varies = 0;

    PrefixSystem(const vector<int>& L, const vector<int>& R, int bit)
        : representation(L.size()), pivot(L.size(), -1) {
        for (size_t i = 0; i < L.size(); ++i) {
            unsigned value = (L[i] ^ R[i]) >> bit;
            unsigned mask = basis.reduce(value);
            if (value != 0) {
                const int lead = 31 - __builtin_clz(value);
                const unsigned marker = 1u << lead;
                basis.vector[lead] = value;
                basis.source[lead] = mask ^ marker;
                pivot[i] = lead;
            } else {
                representation[i] = mask;
                varies |= mask;
            }
        }
    }

    bool admits(Literal literal, unsigned assignment) const {
        const int bit = pivot[literal.interval];
        return bit < 0 || ((varies >> bit) & 1u) ||
               int((assignment >> bit) & 1u) == literal.side;
    }

    bool admits_two(const vector<Literal>& candidates, unsigned assignment) const {
        int freeInterval = -1;
        unsigned freeSides = 0;
        vector<Literal> fixedCandidates;
        for (const auto literal : candidates) {
            if (!admits(literal, assignment)) continue;
            if (pivot[literal.interval] >= 0) {
                fixedCandidates.push_back(literal);
            } else {
                if (freeInterval >= 0 && freeInterval != literal.interval) return true;
                freeInterval = literal.interval;
                freeSides |= 1u << literal.side;
            }
        }

        if (freeInterval >= 0 && !fixedCandidates.empty()) {
            unsigned otherVariation = 0;
            for (size_t i = 0; i < representation.size(); ++i) {
                if (int(i) != freeInterval) otherVariation |= representation[i];
            }
            for (const auto literal : fixedCandidates) {
                const int bit = pivot[literal.interval];
                const int need = literal.side ^ int((assignment >> bit) & 1u);
                const bool sameForm = ((otherVariation >> bit) & 1u) == 0 &&
                                      ((representation[freeInterval] >> bit) & 1u);
                for (int side = 0; side < 2; ++side) {
                    if (((freeSides >> side) & 1u) && compatible(sameForm, need, side)) {
                        return true;
                    }
                }
            }
        }

        if (fixedCandidates.size() < 2) return false;
        XorBasis support;
        for (unsigned mask : representation) support.add(mask);
        unsigned signatures[30]{};
        for (int column = 0; column < 30; ++column) {
            for (unsigned bits = support.vector[column]; bits != 0; bits &= bits - 1) {
                signatures[__builtin_ctz(bits)] |= 1u << column;
            }
        }
        for (size_t i = 0; i < fixedCandidates.size(); ++i) {
            const auto left = fixedCandidates[i];
            const int a = pivot[left.interval];
            const int needA = left.side ^ int((assignment >> a) & 1u);
            for (size_t j = i + 1; j < fixedCandidates.size(); ++j) {
                const auto right = fixedCandidates[j];
                if (left.interval == right.interval) continue;
                const int b = pivot[right.interval];
                const int needB = right.side ^ int((assignment >> b) & 1u);
                const bool sameForm = signatures[a] != 0 && signatures[a] == signatures[b];
                if (compatible(sameForm, needA, needB)) return true;
            }
        }
        return false;
    }
};

int solve(int N, vector<int> L, vector<int> R) {
    unsigned base = 0;
    XorBasis endpoints;
    for (int i = 0; i < N; ++i) {
        base ^= L[i];
        endpoints.add(L[i] ^ R[i]);
    }
    const unsigned baseline = endpoints.maximize(base);

    for (int bit = 29; bit >= 0; --bit) {
        const unsigned suffix = (1u << bit) - 1;
        const unsigned above = (baseline >> bit) & ~1u;
        if ((((above | 1u) << bit) | suffix) <= baseline) continue;

        vector<Literal> unchanged, toggled;
        for (int i = 0; i < N; ++i) {
            if (unsigned(R[i] - L[i]) < suffix) continue;
            const unsigned prefix[2] = {unsigned(L[i]) >> bit, unsigned(R[i]) >> bit};
            for (int side = 0; side < 2; ++side) {
                if (covers_block(L[i], R[i], prefix[side], bit)) unchanged.push_back({i, side});
                if (covers_block(L[i], R[i], prefix[side] ^ 1u, bit)) toggled.push_back({i, side});
            }
        }
        if (unchanged.empty() && toggled.empty()) continue;

        const PrefixSystem system(L, R, bit);
        for (int low = 1; low >= 0; --low) {
            const unsigned prefix = above | unsigned(low);
            const unsigned candidate = (prefix << bit) | suffix;
            if (candidate <= baseline) continue;
            for (const auto recipe : recipes) {
                const unsigned endpointTarget = prefix ^ recipe.parity;
                unsigned remainder = endpointTarget ^ (base >> bit);
                const unsigned assignment = system.basis.reduce(remainder);
                if (remainder != 0) continue;
                const auto& witnesses = recipe.toggle ? toggled : unchanged;
                if (recipe.count == 2) {
                    if (system.admits_two(witnesses, assignment)) return candidate;
                } else {
                    for (const auto literal : witnesses) {
                        if (system.admits(literal, assignment)) return candidate;
                    }
                }
            }
        }
    }
    return baseline;
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
