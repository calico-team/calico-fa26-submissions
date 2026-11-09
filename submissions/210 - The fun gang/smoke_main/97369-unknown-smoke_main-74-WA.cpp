#include <bits/stdc++.h>
using namespace std;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, time;
        cin >> n >> time;
        vector<int> tstamps(n+1);
        tstamps[0] = 0;
        for (int i = 0; i < n; i++) {
            cin >> tstamps[i+1];
        }
        int charges = 2;
        bool works = true;
        for (int i = 1; i < n+1; i++) {
            int max_change = charges + ((tstamps[i] - tstamps[i-1]) / time); // number of charges received in between
            charges = min(2, max_change);
            charges--;
            if (charges < 0) {
                cout << "NO\n";
                works = false;
                break;
            }
        }
        if (works) {
            cout << "YES\n";
        }
    }
    return 0;
}