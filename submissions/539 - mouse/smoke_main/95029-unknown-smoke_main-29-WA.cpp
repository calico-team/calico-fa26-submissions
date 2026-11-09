#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

void solve() {
    int n, r;
    cin >> n >> r;
    pair <int, int> charges;
    pair <int, int> use {true, true};
    vector <int> a(n);
    for (auto &i : a) {
        cin >> i;
    }
    for (const auto &aa : a) {
        if (use.first) {
            if (aa-charges.second >= r) {
                use.second = true;
            }
        }
        else if (aa-charges.first >= 2*r) {
            use.first = true, use.second = true;
        }
        else if (aa-charges.first >= r) {
            use.first = true;
        }
        if (use.first) {
            use.first = false;
            charges.first = aa;
        }
        else if (use.second) {
            use.second = false;
            charges.second = aa;
        }
        else {
            cout << "NO\n";
            cerr << aa << "\n";
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