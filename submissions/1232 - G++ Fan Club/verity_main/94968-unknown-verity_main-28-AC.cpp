#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <bit>
#include <map>
#include <set>
#include <deque>
using namespace std;
using ull = unsigned long long;
void solve() {
    int n, k;
    cin >> n >> k;
    vector<char> a(k), ans(n);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < k; i++) {
        cout << string(n, a[i]) << endl;
        string s;
        cin >> s;
        if (s.find("CORRECT") != string::npos) return;
        for (int j = 0; j < s.size(); j++) {
            if (s[j] != '_') ans[j] = a[i];
        }
    }
    for (char c : ans) cout << c;
    cout << endl;
    string s;
    cin >> s;
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}