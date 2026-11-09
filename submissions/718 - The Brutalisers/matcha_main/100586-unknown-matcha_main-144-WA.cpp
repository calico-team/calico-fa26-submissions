#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> L, R;
long long solve(int b, vector<int>& state) {
    if (b < 0) return 0;
    int fixed = 0;
    vector<int> flex;
    for (int i = 0; i < N; ++i) {
        if (state[i] == 3) return (1LL << (b + 1)) - 1;
        if (state[i] == 0) {
            int bitL = (L[i] >> b) & 1, bitR = (R[i] >> b) & 1;
            if (bitL == bitR) fixed ^= bitL;
            else flex.push_back(i);
        } else if (state[i] == 1) {
            int bitL = (L[i] >> b) & 1;
            if (bitL == 1) fixed ^= 1;
            else flex.push_back(i);
        } else if (state[i] == 2) {
            int bitR = (R[i] >> b) & 1;
            if (bitR == 0) fixed ^= 0;
            else flex.push_back(i);
        }
    }
    if (flex.empty()) {
        return ((long long)fixed << b) | solve(b - 1, state);
    }
    bool can_free = false;
    for (int i : flex) {
        if (state[i] == 1 || state[i] == 2) can_free = true;
    }
    if (can_free) {
        if (flex.size() > 1) return (1LL << (b + 1)) - 1;
        int i = flex[0];
        int out_bit = (state[i] == 1) ? 1 : 0;
        if ((fixed ^ out_bit) == 1) return (1LL << (b + 1)) - 1;
        state[i] = (state[i] == 1) ? 1 : 2; 
        return (1LL << b) | solve(b - 1, state);
    }
    if (flex.size() >= 2) return (1LL << (b + 1)) - 1;
    int i = flex[0];
    state[i] = (fixed == 0) ? 2 : 1; 
    return (1LL << b) | solve(b - 1, state);
}
void run_case() {
    cin >> N;
    L.resize(N); R.resize(N);
    for (int i = 0; i < N; ++i) cin >> L[i];
    for (int i = 0; i < N; ++i) cin >> R[i];
    vector<int> state(N, 0);
    cout << solve(29, state) << "\n";
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    if (cin >> T) while (T--) run_case();
    return 0;
}