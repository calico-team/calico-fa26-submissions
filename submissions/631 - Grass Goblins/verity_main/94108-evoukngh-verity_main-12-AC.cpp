#include<bits/stdc++.h>

using namespace std;

#define int long long
#define INF 1e18

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<char> a(k);
        for (int i = 0; i < k; i++) {
            cin >> a[i];
        }
        vector<char> cor(n, '_');
        bool ja = 0;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) cout << a[i];
            cout << endl;
            string res;
            cin >> res;
            if (res == "CORRECT") {
				ja = 1;
				break;
                for (int j = 0; j < n; j++) {
                    if (cor[j] == '_') cor[j] = a[i];
                }
            } else {
                for (int j = 0; j < n; j++) {
                    if (res[j] != '_') cor[j] = res[j];
                }
            }
        }
        if (!ja) {
			for (char c : cor) cout << c;
			cout << endl;
			string res;
			cin >> res;
		}
    }
}
