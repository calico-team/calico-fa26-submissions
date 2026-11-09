#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, k;
        cin >> n >> k;

        vector<char> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }

        string ans(n, a[0]);

        for (int j = 0; j < k; j++) {
            cout << ans << endl;

            string res;
            cin >> res;

            if (res == "CORRECT") {
                break;
            }

            for (int i = 0; i < n; i++) {
                if (res[i] != '_') {
                    ans[i] = res[i];
                } else {
                    ans[i] = a[(j + 1) % k];
                }
            }
        }
    }

    return 0;
}