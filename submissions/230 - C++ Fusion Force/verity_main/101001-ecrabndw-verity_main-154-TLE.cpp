// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        size_t N, K;
        cin >> N >> K;
        vector<char> letters(K);
        for (size_t i = 0; i < K; i++) cin >> letters[i];

        string ans = "";
        for (size_t i = 0; i < N; i++) ans += '_';
        string s = "";
        for (size_t i = 0; i < K; i++) {
            s = "";
            for (size_t j = 0; j < N; j++) {
                s += letters[i];
            }
            cout << s << endl;
            cin >> s;
            if (s == "CORRECT") break;
            for (size_t j = 0; j < s.size(); j++) {
                if (s[j] != '_') ans[j] = s[j];
            }
        }
        if (s != "CORRECT") cout << ans;
    }
}
