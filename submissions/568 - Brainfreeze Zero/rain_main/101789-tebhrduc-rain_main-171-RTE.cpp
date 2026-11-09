#include <bits/stdc++.h>
using namespace std;
#define int long long

int solve() {
    int N;
    int K;
    cin >> N >> K;
    vector<int> dronexny;
    vector<char> directions;
    int rain = K * N;
    for (int i = 0; i < N; i++) {
        int x;
        int y;
        int z;
        char direction;
        cin >> x >> y >> z >> direction;
        dronexny.push_back(x + y);
        directions.push_back(direction);
    }

    vector<int> seen_pos;
    vector<char> seen_dir;

    for (int i = 0; i < N; i++) {
        int pos = dronexny[i];
        bool contains;
        if (find(seen_pos.begin(), seen_pos.end(), pos) != seen_pos.end()) {
            contains = true;
        }

        if (contains) {
            if (seen_dir[distance(seen_pos.begin(), find(seen_pos.begin(), seen_pos.end(), pos))] != directions[i]) {
                rain -= 1;
            }
        } else {
            seen_pos.push_back(pos);
            seen_dir.push_back(directions[i]);
        }
    }

    cout << rain;
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