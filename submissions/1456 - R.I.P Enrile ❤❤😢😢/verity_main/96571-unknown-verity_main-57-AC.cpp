// Nov 09 2026, 08:53

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define fastIO cin.tie(NULL); ios::sync_with_stdio(NULL)
#define fi first
#define se second

int main() {
    fastIO;

    int T; cin >> T;
    while(T--) {
        int n, k; cin >> n >> k;
        vector<char> ans(n, '_');
        vector<char> verity(k); for(auto &i : verity) cin >> i;

        for(auto c : verity) {
            for(int i = 0; i < n; i++) {
                cout << (ans[i] == '_' ? c : ans[i]);
            } cout << endl;

            string s; cin >> s;
            if(s == "CORRECT") break;
            for(int i = 0; i < n; i++) {
                if(s[i] != '_') ans[i] = s[i];
            }
        }
    }

    return 0;
}