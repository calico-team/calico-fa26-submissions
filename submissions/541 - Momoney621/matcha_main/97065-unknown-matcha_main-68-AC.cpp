#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int BITS = 30;

int getBit(int x, int b) {
    return (x >> b) & 1;
}

int solve(vector<int>& L, vector<int>& R) {
    int n = L.size();

    int base = 0;
    vector<int> best(n, 0);
    vector<int> worse(n, 0);
    vector<vector<int>> groups(BITS);
    int upCount[BITS] = {};
    bool hasTie[BITS] = {};

    for (int i = 0; i < n; i++) {
        if (L[i] == R[i]) {
            base ^= L[i];
            continue;
        }
        int h = 31 - __builtin_clz(L[i] ^ R[i]);
        int lowMask = (1 << h) - 1;
        int up = ~L[i] & lowMask;
        int down = R[i] & lowMask;

        base ^= R[i] & ~lowMask;
        best[i] = max(up, down);
        worse[i] = min(up, down);
        if (up > down) upCount[h]++;
        if (up == down) hasTie[h] = true;
        groups[h].push_back(i);
    }

    vector<vector<int>> mustSwap(BITS);
    for (int h = BITS - 1; h >= 0; h--) {
        if (groups[h].empty()) continue;
        bool odd = (getBit(base, h) == 0);
        if (odd) base ^= (2 << h) - 1;
        if (upCount[h] % 2 != odd && !hasTie[h]) mustSwap[h] = groups[h];
    }

    int setCount[BITS] = {};
    for (int i = 0; i < n; i++)
        for (int b = 0; b < BITS; b++)
            if (getBit(best[i], b)) setCount[b]++;

    int answer = 0;
    for (int t = BITS - 1; t >= 0; t--) {
        int total = setCount[t] + getBit(base, t);

        int gain[BITS] = {};
        for (int h = 0; h < BITS; h++) {
            if (mustSwap[h].empty()) continue;
            gain[h] = -1;
            for (int j : mustSwap[h]) {
                int change = getBit(worse[j], t) - getBit(best[j], t);
                gain[h] = max(gain[h], change);
            }
            total += gain[h];
        }

        if (total >= 2) return answer | ((2 << t) - 1);
        answer |= total << t;

        for (int h = 0; h < BITS; h++) {
            vector<int> kept;
            for (int j : mustSwap[h]) {
                int change = getBit(worse[j], t) - getBit(best[j], t);
                if (change == gain[h]) kept.push_back(j);
            }
            mustSwap[h] = kept;
        }
    }
    return answer;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<int> L(n), R(n);
        for (int i = 0; i < n; i++) cin >> L[i];
        for (int i = 0; i < n; i++) cin >> R[i];
        cout << solve(L, R) << '\n';
    }
    return 0;
}
