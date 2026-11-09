#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int T; cin >> T;
    while (T--) {
        int N; long long R; cin >> N >> R;
        long long Ready = 0; int C = 2; bool Ok = 1;
        for (int i = 0; i < N; i++) {
            long long A; cin >> A;
            while (C < 2 && Ready <= A) C++, Ready += R;
            if (!C) Ok = 0;
            else if (C-- == 2) Ready = A + R;
        }
        cout << (Ok ? "YES" : "NO") << '\n';
    }
}