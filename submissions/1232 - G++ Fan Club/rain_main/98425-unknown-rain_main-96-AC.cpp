#include <bits/stdc++.h>

using namespace std;

struct pos {
    long long x;
    long long y;

    bool operator<(const pos& b) const
    {
        return x < b.x;
    }
};

int main() {
    int t;
    cin >> t;

    vector<int> indices;

    while (t--)
    {
        int n;
        long long k;
        cin >> n >> k;

        vector<pos> ndrones;
        unordered_map<long long, vector<pos>> edrones;

        for (int i{}; i < n; i++)
        {
            long long x, y, z;
            cin >> x >> y >> z;
            char d;
            cin >> d;
            if (d == 'E')
            {
                edrones[x+y].push_back({x, y});
            }
            else
            {
                ndrones.push_back({x, y});
            }
        }

        long long total{n * k};

        for (pair<const long long, vector<pos>>& group : edrones)
        {
            sort(group.second.begin(), group.second.end());
        }

        long long blocks{};

        for (pos ndrone : ndrones)
        {
            long long sum{ndrone.x + ndrone.y};
            vector<pos>&  group{edrones[sum]};

            long long intersections{upper_bound(group.begin(), group.end(), pos{ndrone.x, 0}) - lower_bound(group.begin(), group.end(), pos{ndrone.x - k + 1, 0})};

            blocks += intersections;
        }

        cout << total - blocks << endl;
    }

    return 0;
}