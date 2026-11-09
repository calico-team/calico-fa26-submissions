// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

struct Drone {
    long long x, y, z;
    char d;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int N;
        long long K;
        cin >> N >> K;

        vector<Drone> a(N);

        for (int i = 0; i < N; i++) {
            cin >> a[i].x >> a[i].y
                >> a[i].z >> a[i].d;
        }

        long long total = 1LL * N * K;

        set<pair<long long, int>> blocked;

        for (int i = 0; i < N; i++) {
            for (int j = i + 1; j < N; j++) {

                if (a[i].d == a[j].d)
                    continue;

                int e = i, n = j;

                if (a[e].d != 'E')
                    swap(e, n);

                long long t1 = a[n].x - a[e].x;
                long long t2 = a[e].y - a[n].y;

                if (t1 == t2 && t1 >= 0 && t1 < K) {
                    int lower = (a[i].z < a[j].z) ? i : j;

                    blocked.insert({t1, lower});
                }
            }
        }

        total -= blocked.size();

        cout << total << '\n';
    }
}
