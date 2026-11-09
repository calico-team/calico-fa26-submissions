#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, cd;

    cin >> n >> cd;
    
    int curr_a = 0;
    int charge = 2;
    int next_one = cd;

    // cout << "n: " << n;
    // cout << " cd: " << cd << "\n";

    bool works = true;

    for (int i = 0; i < n; i++) {
        cin >> curr_a; 


        if (curr_a >= next_one + cd) {
            charge = 2;
        } else if (curr_a >= next_one) {
            charge++;
        }

        if (charge >= 2) {
            charge = 2;
            next_one = curr_a;
        }

        charge--;

        if (charge < 0) {
            works = false;
        }

        if (curr_a >= next_one) {
            next_one += cd;
        }

        // cout << "curr a: " << curr_a << " charge: " << charge << " next_one: " << next_one << "\n";
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
