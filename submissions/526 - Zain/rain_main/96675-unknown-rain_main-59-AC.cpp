
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        long long K;
        cin >> N >> K;

        vector<pair<long long, long long>> east, north;

        for (int i = 0; i < N; i++) {
            long long x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            if (d == 'E')
                east.push_back({x + y, x});
            else
                north.push_back({x + y, x});
        }

        sort(east.begin(), east.end());

        long long ans = 1LL * N * K;

        for (auto [sum, x] : north) {

            // Valid east-drone starting x positions
            auto left = lower_bound(
                east.begin(), east.end(),
                make_pair(sum, x - K + 1)
            );

            auto right = upper_bound(
                east.begin(), east.end(),
                make_pair(sum, x)
            );

            // Each overlap loses one unit of water
            ans -= (right - left);
        }

        cout << ans << '\n';
    }

    return 0;
}
