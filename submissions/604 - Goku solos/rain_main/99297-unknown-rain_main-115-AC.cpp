
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

        const int MAX_SUM = 200000;

        vector<vector<int>> east(MAX_SUM + 1);
        vector<vector<int>> north(MAX_SUM + 1);

        for (int i = 0; i < N; i++) {
            int X, Y, Z;
            char D;

            cin >> X >> Y >> Z >> D;

            int sum = X + Y;

            if (D == 'E') {
                east[sum].push_back(X);
            } else {
                north[sum].push_back(X);
            }
        }

        long long meetings = 0;

        for (int s = 0; s <= MAX_SUM; s++) {
            auto &E = east[s];
            auto &Npoints = north[s];

            sort(E.begin(), E.end());

            for (int x : Npoints) {
                long long low = (long long)x - (K - 1);

                auto L = lower_bound(E.begin(), E.end(), low);
                auto R = lower_bound(E.begin(), E.end(), x);

                meetings += R - L;
            }
        }

        long long answer = (long long)N * K - meetings;

        cout << answer << '\n';
    }

    return 0;
}
