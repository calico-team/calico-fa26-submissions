#include <bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (!(cin >> t)) return 0;
    while (t--) {
        int n, k;
        if (!(cin >> n >> k)) break;
        vector<char> alphabet(k);
        for (int i = 0; i < k; i++) {
            cin >> alphabet[i];
        }
        string guess(n, k > 0 ? alphabet[0] : 'A');
        for (int i = 0; i < n; i++) {
            if (k > 0) {
                guess[i] = alphabet[i % k];
            }
        }
        string response;
        while (cout << guess << endl && cin >> response && response != "CORRECT") {
        }
    }
}