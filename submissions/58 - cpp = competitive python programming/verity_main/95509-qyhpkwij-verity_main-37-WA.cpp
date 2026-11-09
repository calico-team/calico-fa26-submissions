#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<char> chs; chs.resize(k);
        for (int i = 0; i < k; i++) cin >> chs[i];
        vector<char> ans; ans.resize(k);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < n; j++) cout << chs[i];
            cout << endl << flush;

            std::string ret; cin >> ret;
            for (int j = 0; j < n; j++) {
                if (ret[j] != '_') {
                    ans[j] = chs[i];
                }
            }
        }

        for (char c : ans) cout << c;
        cout << endl << flush;

        std::string corr; cin >> corr;
    }
    return 0;
}