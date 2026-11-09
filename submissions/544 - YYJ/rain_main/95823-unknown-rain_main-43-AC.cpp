#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, k; cin >> n >> k;
        vector<array<int, 3>> north, east;
        for (int i = 0; i < n; i++) {
            int x, y, z; char d; cin >> x >> y >> z >> d;
            if (d == 'N') north.push_back({x, y, z});
            else east.push_back({x, y, z});
        }
        sort(north.begin(), north.end());
        sort(east.begin(), east.end());
        
        vector<vector<int>> sums(200005); // sums[val] = (east drones where x + y = val)
        int j = 0;
        long long cover = 0;
        for (int i = 0; i < north.size(); i++) {
            while (j < east.size() && east[j][0] <= north[i][0]) {
                sums[east[j][0] + east[j][1]].push_back(east[j][0]);
                j++;
            }
            int val = north[i][0] + north[i][1];
            int idx = (int) (upper_bound(sums[val].begin(), sums[val].end(), north[i][0] - k) - sums[val].begin());
            cover += (long long) sums[val].size() - idx;
        }
        cout << (long long) k * n - cover << "\n";
    }
}
