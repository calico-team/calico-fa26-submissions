#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector <char> a(k);
        for (auto &i : a) {
            cin >> i;
        }
        string ans;
        for (int i = 0; i < n; i++) {
            ans += "_";
        }
        bool good = false;
        for (const char &c : a) {
            for (int i = 0; i < n; i++) {
                cout << c;
            }
            cout << endl;
            string cur;
            cin >> cur;
            if (cur == "CORRECT") {
                good = true;
                break;
            }
            for (int i = 0; i < (int) cur.size(); i++) {
                if (cur[i] != '_') {
                    ans[i] = cur[i];
                }
            }
        }
        if (!good) {
            cout << ans << "\n";
            string s;
            cin >> s;
        }
    }
}