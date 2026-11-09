// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        size_t N, K;
        cin >> N >> K;
        long long ans = N*K;
        map<int, vector<pair<int, bool>>> blah; // <x + y, [x, d]>
        for (size_t i = 0; i < N; i++) {
            char tmp = ' ';
            int x, y, z;
            cin >> x >> y >> z >> tmp;
            bool d = (tmp == 'N');
            if (d)
                for (auto [xj, dj] : blah[x + y]) {
                    if (dj) continue;
                    if (xj < x && x - xj < (int)K) ans--;
                }

            if (blah.find(x + y) == blah.end()) blah[x + y] = {};
            blah[x + y].push_back(make_pair(x, d));
        }

        cout << ans << endl;
    }
}
