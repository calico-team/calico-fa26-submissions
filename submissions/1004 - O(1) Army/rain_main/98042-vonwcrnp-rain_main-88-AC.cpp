#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n;
        long long nights;
        cin >> n >> nights;
        vector<pair<int, int>> east, north;
        for (int i = 0; i < n; ++i) {
            int x, y, z;
            char direction;
            cin >> x >> y >> z >> direction;
            (direction == 'E' ? east : north).emplace_back(x + y, x);
        }
        sort(east.begin(), east.end());
        sort(north.begin(), north.end());
        long long result = n * nights;
        for (auto [diagonal, x] : east) {
            auto first = lower_bound(north.begin(), north.end(), pair{diagonal, x + 1});
            auto last = lower_bound(first, north.end(), pair{diagonal, int(x + nights)});
            result -= last - first;
        }
        cout << result << '\n';
    }
}
