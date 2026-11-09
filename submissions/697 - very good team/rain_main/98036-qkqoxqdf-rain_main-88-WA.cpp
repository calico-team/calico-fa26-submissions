#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 1e6 + 1;
int N, K, T;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> N >> K;
        vector<pair<int, int>> east;
        vector<pair<int, int>> north;
        ll cnt = 1LL * K * N;
        for (int j = 0; j < N; j++)
        {
            int x, y, z; char d; cin >> x >> y >> z >> d;
            if (d == 'N')
            {
                north.emplace_back(x, y);
            } else east.emplace_back(x, y);
        }
        unordered_map<int, vector<int>> total;
        for (auto [xj, yj] : north) total[xj + yj].push_back(xj);
        for (auto [a, b] : total) sort(b.begin(), b.end());
        for (auto [xi, yi] : east)
        {
            int left = lower_bound(total[xi + yi].begin(), total[xi+yi].end(), xi) - total[xi + yi].begin();
            int right = lower_bound(total[xi + yi].begin(), total[xi+yi].end(), xi + K) - total[xi + yi].begin();
            cnt -= (right - left);
        }
        cout << cnt << "\n";
    }
}