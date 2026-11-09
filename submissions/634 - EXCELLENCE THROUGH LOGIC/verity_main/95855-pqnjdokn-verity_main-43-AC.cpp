
#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<char> alphabet(k);

    for (int i = 0; i < k; i++) {
        cin >> alphabet[i];
    }

    string answer(n, '?');

    for (int j = 0; j < k; j++) {
        string guess = answer;

        for (int i = 0; i < n; i++) {
            if (guess[i] == '?') {
                guess[i] = alphabet[j];
            }
        }

        cout << guess << endl;

        string response;
        cin >> response;

        if (response == "CORRECT") {
            return;
        }

        for (int i = 0; i < n; i++) {
            if (response[i] != '_') {
                answer[i] = response[i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}
