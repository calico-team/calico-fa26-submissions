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
        cout << string(a[i], n) << endl;
        string s;
        cin >> s;
        if (s.find("CORRECT") != string::npos) return;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '_') ans[i] = a[i];
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