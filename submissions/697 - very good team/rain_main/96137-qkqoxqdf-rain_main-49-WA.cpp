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
        ll cnt = K * N;
        for (int j = 0; j < N; j++)
        {
            int x, y, z; char d; cin >> x >> y >> z >> d;
            if (d == 'N')
            {
                north.push_back({x, y});
            } else east.push_back({x, y});
        }

        for (auto [xi, yi] : east)
        {
            for (auto [xj, yj] : north)
            {
                int a = xj - xi;
                if (a >= 0 && a == yi - yj && a < K)
                {
                    cnt--;
                }
            }
        }
        cout << cnt << "\n";
    }
}