// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        size_t N, K;
        cin >> N >> K;
        int maxx = 0, maxy = 0;
        char tmp = ' ';
        vector<int> x(N), y(N), z(N);
        vector<bool> d(N);
        map<pair<int, int>, size_t> coords;
        for (size_t i = 0; i < N; i++) {
            cin >> x[i] >> y[i] >> z[i] >> tmp;
            d[i] = (tmp == 'N');
            maxx = max(maxx, x[i]);
            maxy = max(maxy, y[i]);
            coords[make_pair(x[i], y[i])] = i;
        }

        // for (int i = 0; i < N; i++) cout << x[i] << " "; cout << endl;
        // for (int i = 0; i < N; i++) cout << y[i] << " "; cout << endl;
        // for (int i = 0; i < N; i++) cout << z[i] << " "; cout << endl;
        // for (int i = 0; i < N; i++) cout << d[i] << " "; cout << endl;
        // cout << maxx << ", " << maxy << endl;
        // for (auto [coord, id] : coords) {
        //     cout << coord.first << ", " << coord.second << ": " << id << endl;
        // }

        int ans = 0;
        for (size_t n = 0; n < N; n++) {
            ans += K;
            for (int i = 0; i < (int)K; i++) {
                if (d[n]) { // moving up
                    if (x[n] - i < 0) break;
                    pair<int, int> coord = make_pair(x[n] - i, y[n] + i);
                    if (coords.find(coord) != coords.end() && !d[coords[coord]] && z[coords[coord]] > z[n]) ans--;// {ans--; cout << coord.first << " " << coord.second << endl;}
                } else { // moving right
                    if (y[n] - i < 0) break;
                    pair<int, int> coord = make_pair(x[n] + i, y[n] - i);
                    if (coords.find(coord) != coords.end() && d[coords[coord]] && z[coords[coord]] > z[n]) ans--; //{ans--; cout << coord.first << " " << coord.second << endl;}
                }
            }
        }
        cout << ans << endl;
    }
}
