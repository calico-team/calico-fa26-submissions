
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> L(n), R(n);

    for (int i = 0; i < n; i++) cin >> L[i];
    for (int i = 0; i < n; i++) cin >> R[i];

    int answer = 0;

    for (int bit = 29; bit >= 0; bit--) {
        vector<int> flexible;
        int fixedXor = 0;

        for (int i = 0; i < n; i++) {
            int a = (L[i] >> bit) & 1;
            int b = (R[i] >> bit) & 1;

            if (a != b) {
                flexible.push_back(i);
            } else {
                fixedXor ^= a;
            }
        }

        int target = fixedXor;

        if (!flexible.empty()) {
            target = 1;
            answer |= (1 << bit);
        }

        vector<int> chosen(n, 0);

        for (int i = 0; i < n; i++) {
            chosen[i] = (L[i] >> bit) & 1;
        }

        if (!flexible.empty()) {
            int need = fixedXor ^ target;

            if (need) {
                chosen[flexible[0]] = 1;
            }

            for (int j = 1; j < (int)flexible.size(); j++) {
                chosen[flexible[j]] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            int block = 1 << (bit + 1);
            int half = 1 << bit;

            int base = (L[i] / block) * block;
            int low = base + chosen[i] * half;
            int high = low + half - 1;

            L[i] = max(L[i], low);
            R[i] = min(R[i], high);
        }
    }

    cout << answer << '\n';
}

void read_your_input() {
    int testCases;
    cin >> testCases;

    while (testCases--) {
        solve();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_your_input();
    return 0;
}
