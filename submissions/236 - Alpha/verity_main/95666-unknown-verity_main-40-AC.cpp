#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<char> a(k);
        for (char &c : a) cin >> c;
        string s(n, '_');
        for (char c : a) {
            string g = s;
            for (char &x : g) if (x == '_') x = c;
            cout << g << endl;
            cin >> s;
            if (s == "CORRECT") break;}}}