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

// cvc5 synthesized the bounds and the minimal witness recipe set.
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

// Truncated endpoint choices form a linear system over GF(2).
// Each nonpivot column records how it changes the pivot variables.
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