#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, cd;

    cin >> n >> cd;
    
    int curr_a = 0;
    int charge = 2;
    int next_one = 0;
    int next_full = 0;

    // cout << " n: " << n;
    // cout << " cd: " << cd << " ";

    bool works = true;

    for (int i = 0; i < n; i++) {
        cin >> curr_a; 

        if (curr_a >= next_one) {
            charge++;
        } else if (curr_a >= next_full) {
            charge = 2;
        }

        if (charge >= 2) {
            charge = 2;
            next_one = curr_a;
        }

        charge--;

        if (charge < 0) {
            works = false;
        }
        next_one = next_one + cd;
        next_full = next_one + (1 - charge) * cd;
    }
    if (works) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); 
    
    int tc;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
    }
}
