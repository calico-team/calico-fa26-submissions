#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    pair <int, int> usable {0, 0};
    vector <int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    for (const auto &aa : a) {
        if (usable.first <= aa) {
            usable.first = max(usable.second, aa)+r;
        }
        else if (usable.second <= aa) {
            usable.second = max(usable.first, aa)+r;
        }
        else {
            cout << "NO\n";
            return;
        }
    }
    cout << "YES\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}