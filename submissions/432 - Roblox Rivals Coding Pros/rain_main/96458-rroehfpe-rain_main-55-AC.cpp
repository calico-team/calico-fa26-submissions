#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <cmath>
#include <cctype>
#include <numeric>
#include <iomanip>
#include <climits>
#include <list>
using namespace std;



int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(12);

    int T;
    cin >> T;

    for (int t = 0; t < T; t++) {
        int N;
        long long K;
        cin >> N >> K;

        // for east and north drones to intersect:
        // (xE+t, yE), (xN, yN+t)
        // -> xE+t = xN, yE-t = yN
        // xE+t + yE-t = xN + yN
        // xE + yE = xN + yN
        unordered_map<int, vector<int>> edrones_sum, ndrones_sum;
        for (int i = 0; i < N; i++) {
            int x,y,z;
            char d;
            cin >> x >> y >> z >> d;

            if (d == 'E') {
                edrones_sum[x + y].push_back(x);
            } else {
                ndrones_sum[x + y].push_back(x);
            }
        }

        // (xE+t, yE), (xN, yN+t)
        // t = xN - xE
        // 0 <= t < K
        // 0 <= xN-xE < K
        // xE <= xN < xE + K
        long long water = (long long)N*K;
        for (auto [sum, edrones] : edrones_sum) {
            if (ndrones_sum.count(sum)) {
                sort(ndrones_sum[sum].begin(), ndrones_sum[sum].end());

                for (int xE : edrones) {
                    water -= lower_bound(ndrones_sum[sum].begin(), ndrones_sum[sum].end(), xE + K) - lower_bound(ndrones_sum[sum].begin(), ndrones_sum[sum].end(), xE);
                }
            }

        }

        cout << water << "\n";
    }

    
    return 0;
}