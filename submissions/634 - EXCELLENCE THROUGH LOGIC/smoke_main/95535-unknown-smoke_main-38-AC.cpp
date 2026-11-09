
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    long long r;
    cin >> n >> r;

    queue<long long> recharge;
    int charges = 2;
    bool possible = true;

    for (int i = 0; i < n; i++) {
        long long time;
        cin >> time;

        while (!recharge.empty() && recharge.front() <= time) {
            charges++;
            recharge.pop();
        }

        if (charges == 0) {
            possible = false;
        } else {
            charges--;

            long long readyTime = time + r;

            if (!recharge.empty()) {
                readyTime = recharge.back() + r;
            }

            recharge.push(readyTime);
        }
    }

    cout << (possible ? "YES" : "NO") << '\n';
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
