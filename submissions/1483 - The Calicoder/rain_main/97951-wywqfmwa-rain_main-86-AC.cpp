#include <bits/stdc++.h>
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

        map<long long, vector<long long>> east, north;

        for (int i = 0; i < N; i++) {
            long long x, y, z;
            char d;
            cin >> x >> y >> z >> d;

            long long sum = x + y;

            if (d == 'E')
                east[sum].push_back(x);
            else
                north[sum].push_back(x);
        }

        long long ans = 1LL * N * K;

        for (auto &[sum, E] : east) {
            if (!north.count(sum))
                continue;

            auto &Nvec = north[sum];
            sort(Nvec.begin(), Nvec.end());

            for (long long x : E) {
                auto l = lower_bound(
                    Nvec.begin(), Nvec.end(), x
                );

                auto r = lower_bound(
                    Nvec.begin(), Nvec.end(), x + K
                );

                ans -= (r - l);
            }
        }

        cout << ans << '\n';
    }
}