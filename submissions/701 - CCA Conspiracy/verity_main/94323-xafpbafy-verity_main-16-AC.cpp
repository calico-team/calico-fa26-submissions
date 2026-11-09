#include <bits/stdc++.h>
using namespace std;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<char> used(k);
    for (int i = 0; i < k; i++) {
        cin >> used[i];
    }
    string known(n, '?');
    for (int i = 0; i < k; i++) {
        char c = used[i];
        string guess = known;
        for (int j = 0; j < n; j++) {
            if (guess[j] == '?') {
                guess[j] = c;
            }
        }
        cout << guess << endl;
        string response;
        cin >> response;
        if (response == "CORRECT") {
            return;
        }
        for (int j = 0; j < n; j++) {
            if (response[j] != '_') {
                known[j] = response[j];
            }
        }
    }
}
int main() {
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
}