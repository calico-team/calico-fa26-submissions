#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pull = pair<ull, ull>;

int main() {
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<char> chars(k);
        for (int j = 0; j < k; j++) {
            cin >> chars[j];
        }

        vector<int> guess(n);
        while (true) {
            for (int i = 0; i < n; i++) {
                cout << chars[guess[i]];
            }
            cout << endl;
            cout.flush();

            string feedback;
            cin >> feedback;

            if (feedback == "CORRECT") {
                break;
            }

            for (int i = 0; i < n; i++) {
                if (feedback[i] == '_') {
                    guess[i]++;
                }
            }
        }
    }


}