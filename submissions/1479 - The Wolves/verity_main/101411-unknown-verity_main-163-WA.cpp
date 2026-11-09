// November 8, 2026
// August Makan
// Starter

// imports everything and creates shortcuts
#include <bits/stdc++.h>
using namespace std;
#define mk(a) int a; cin >> a
#define ms(s) string s; cin >> s
#define ml(l) ll l; cin >> l
#define out(x) cout << x << "\n"
#define outnl(x) cout << x
#define vi(v) vector<int> v
#define vs(v) vector<string> v
#define pb push_back
#define rep(i, n) for (int i = 0; i < n; i++)
#define ll long long

int main() {

    mk(tc);
    while (tc--) {
        mk(n); mk(k);
        string s(n, ' ');
        for (int i = 0; i < k; i++) {
            char tmp;
            cin >> tmp;
            s[i] = tmp;
        }
        for (int i = k; i < n; i++) {
            s[i] = s[i % k];
        }
        out(s);
        ms(feedback);
        string res(n, '_');
        string prevS = s;
        int pos = 1;
        while ("CORRECT" != feedback) {
            for (int i = 0; i < feedback.length(); i++) {
                if (feedback[i] != '_') {
                    res[i] = feedback[i];
                }
            }


            string ans(n, ' ');
            for (int i = 0; i < n; i++) {
                ans[i] = s[(i + pos) % k];
            }
            for (int i = 0; i < n; i++) {
                if (res[i] != '_') ans[i] = res[i];
            }
            out(ans);
            prevS = ans;
            cin >> feedback;
            pos++;


        }
    }
    // ends program
    return 0;
}