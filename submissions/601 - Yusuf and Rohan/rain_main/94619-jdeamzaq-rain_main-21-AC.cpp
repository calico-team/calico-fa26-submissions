#include <bits/stdc++.h>
using namespace std;

struct Drone {
    int sum, x;
    char dir;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        int n;
        long long k;
        cin >> n >> k;

        vector<Drone> a(n);
        for (auto &v : a) {
            int y, z;
            cin >> v.x >> y >> z >> v.dir;
            v.sum = v.x + y;
        }

        sort(a.begin(), a.end(), [](const Drone &u, const Drone &v) {
            if (u.sum != v.sum) return u.sum < v.sum;
            return u.x < v.x;
        });

        long long blocked = 0;
        int start = 0;

        while (start < n) {
            int end = start;
            while (end < n && a[end].sum == a[start].sum)
                ++end;

            int left = start;
            long long east = 0;

            for (int i = start; i < end; ++i) {
                while (left < i && (long long)a[left].x + k <= a[i].x) {
                    if (a[left].dir == 'E')
                        --east;
                    ++left;
                }

                if (a[i].dir == 'N')
                    blocked += east;
                else
                    ++east;
            }

            start = end;
        }

        cout << n * k - blocked << '\n';
    }

    return 0;
}
