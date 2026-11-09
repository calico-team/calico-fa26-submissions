#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    char c[k];
    for (int i = 0; i < k; i++) {
        cin >> c[i];
    }

    string stop;
    int idx = 1;

    string guess(n, c[0]);

    cout << guess << "\n";
    cin >> stop;

    while (stop != "CORRECT") {
        for (int i = 0; i < n; i++) {
            if (stop[i] == '_') guess[i] = c[idx];
        }
        cout << guess << "\n";
        idx++;
        cin >> stop;
    }
}

int main() {
	int tc;
    cin >> tc;

    while (tc--) {
        solve();
    }
}
