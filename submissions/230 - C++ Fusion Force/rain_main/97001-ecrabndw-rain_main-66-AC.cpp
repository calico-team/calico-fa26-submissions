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
        char tmp = ' ';
        vector<int> x(N), y(N), z(N);
        vector<bool> d(N);
        map<int, vector<size_t>> diagonals;
        for (size_t i = 0; i < N; i++) {
            cin >> x[i] >> y[i] >> z[i] >> tmp;
            d[i] = (tmp == 'N');
            
            for (size_t j : diagonals[x[i] + y[i]]) {
                if (d[j] == d[i]) continue;
                // if (z[j] <= z[i]) continue;
                if (d[i] && x[j] < x[i] && x[i] - x[j] < (int)K) ans--;
                if (!d[i] && x[i] < x[j] && x[j] - x[i] < (int)K) ans--;
            }

            if (diagonals.find(x[i] + y[i]) == diagonals.end()) diagonals[x[i] + y[i]] = {};
            diagonals[x[i] + y[i]].push_back(i);
        }

        cout << ans << endl;
    }

}
