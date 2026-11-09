#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve() {
    int N;
    int R;
    cin >> N >> R;
    vector<int> times;
    for (int i = 0; i < N; i++) {
        int time;
        cin >> time;
        times.push_back(time);
    }

    int charges = 2;
    int previous_time;

    for (int i = 0; i < N; i++) {
        int time = times[i];

        if (time - previous_time >= R && charges != 2) {
            charges += floor(time - previous_time / 10);
        }

        if (charges == 0) {
            cout << "NO" << endl;
            return 0;
        }
        
        charges -= 1;
        previous_time = time;
    }

    cout << "YES" << endl;
    return 0;

}

int32_t main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        solve();
    }
    return 0;
}