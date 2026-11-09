// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;

    while (T--) {
        int N;
        long long R;
        cin >> N >> R;

        queue<long long> recharge;
        bool possible = true;

        for (int i = 0; i < N; i++) {
            long long A;
            cin >> A;

            if (!possible) continue;

            while (!recharge.empty() && recharge.front() <= A) {
                recharge.pop();
            }

            if (recharge.size() == 2) {
                possible = false;
            } else {
                long long start = A;

                if (!recharge.empty()) {
                    start = max(start, recharge.back());
                }

                recharge.push(start + R);
            }
        }

        cout << (possible ? "YES" : "NO") << '\n';
    }
}
