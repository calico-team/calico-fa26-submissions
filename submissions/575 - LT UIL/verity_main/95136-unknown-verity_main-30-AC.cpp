#include <bits/stdc++.h>
using namespace std;

int main() {

    int t; cin >> t;

    for (int tc = 0; tc < t; tc++) {
        int n; int k; cin >> n; cin >> k;
        vector<char> possible_chars(k);
        for (int i = 0; i < k; i++) {
            char c; cin >> c;
            possible_chars[i] = c;
        }
        string ans = "";
        for (int i = 0; i < n; i++) {
            ans += "_";
        }
        bool passed = false;
        for (int i = 0; i < k; i++) {
            string curr_guess = "";
            for (int j = 0; j < n; j++) {
                curr_guess += possible_chars[i];
            }
            cout << curr_guess << endl;
            string response;
            cin >> response;
            if (response == "CORRECT") {
                passed = true;
                break;
            }
            for (int j = 0; j < n; j++) {
                if (response[j] != '_') {
                    ans[j] = possible_chars[i];
                }
            }
        }
        if (!passed) {
            cout << ans << endl;
            string bs; cin >> bs;
        }
    }
}