#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) {
        int N, K;
        cin >> N >> K;
        vector<char> arr(K);
        for (char& c : arr) {
            cin >> c;
        }
        string res(N, arr[0]);
        for (int i = 1; i <= K; ++i) {
            cout << res << endl;
            cin >> res;
            if (res == "CORRECT") {
                break;
            }
            for (char& j : res) {
                if (j == '_') {
                    j = arr[i];
                }
            }
        }
    }
}