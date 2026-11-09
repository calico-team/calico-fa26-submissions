#include <bits/stdc++.h>
using namespace std;

static constexpr int BITS = 30;
static constexpr int MASK = (1 << BITS) - 1;

// Returns x in [L, R] maximizing (x XOR mask).
static int bestValue(int L, int R, int mask) {
    int prefix = 0;
    for (int bit = BITS - 1; bit >= 0; --bit) {
        int wantX = ((mask >> bit) & 1) ^ 1; // makes this XOR bit equal to 1
        int candidate = prefix | (wantX << bit);
        int low = candidate;
        int high = low + ((1 << bit) - 1);
        if (max(low, L) <= min(high, R)) {
            prefix = candidate;
        } else {
            prefix |= ((wantX ^ 1) << bit);
        }
    }
    return prefix;
}

static long long exactSolve(const vector<int>& L, const vector<int>& R) {
    int n = (int)L.size();
    vector<int> chosen(n);
    int answer = 0;
    function<void(int,int)> dfs = [&](int i, int xr) {
        if (i == n) {
            answer = max(answer, xr);
            return;
        }
        for (int x = L[i]; x <= R[i]; ++x) {
            dfs(i + 1, xr ^ x);
        }
    };
    dfs(0, 0);
    return answer;
}

static int improve(const vector<int>& L, const vector<int>& R,
                   vector<int> x, int rounds) {
    int n = (int)L.size();
    int current = 0;
    for (int v : x) current ^= v;
    mt19937 rng(712367821);
    vector<int> order(n);
    iota(order.begin(), order.end(), 0);

    for (int pass = 0; pass < rounds; ++pass) {
        if (pass & 1) reverse(order.begin(), order.end());
        else shuffle(order.begin(), order.end(), rng);
        bool changed = false;
        for (int id : order) {
            int without = current ^ x[id];
            int nx = bestValue(L[id], R[id], without);
            if (nx != x[id]) {
                x[id] = nx;
                current = without ^ nx;
                changed = true;
            }
        }
        if (!changed) break;
    }
    return current;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;
    while (T--) {
        int N;
        cin >> N;
        vector<int> L(N), R(N);
        for (int &v : L) cin >> v;
        for (int &v : R) cin >> v;

        // Exact enumeration is useful for small products of interval sizes.
        const long long LIMIT = 1500000;
        long long combinations = 1;
        for (int i = 0; i < N; ++i) {
            long long width = (long long)R[i] - L[i] + 1;
            if (combinations > LIMIT / width) {
                combinations = LIMIT + 1;
                break;
            }
            combinations *= width;
        }

        if (combinations <= LIMIT) {
            cout << exactSolve(L, R) << '\n';
            continue;
        }

        int answer = 0;
        vector<vector<int>> starts;
        starts.emplace_back(N);
        for (int i = 0; i < N; ++i) starts[0][i] = L[i];
        starts.emplace_back(N);
        for (int i = 0; i < N; ++i) starts[1][i] = R[i];
        starts.emplace_back(N);
        for (int i = 0; i < N; ++i) starts[2][i] = (L[i] + R[i]) / 2;

        for (auto &start : starts) answer = max(answer, improve(L, R, start, 12));
        cout << answer << '\n';
    }
}
