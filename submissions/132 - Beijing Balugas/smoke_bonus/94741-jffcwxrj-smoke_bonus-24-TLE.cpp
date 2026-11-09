// Source: https://usaco.guide/general/io

#include <bits/stdc++.h>
using namespace std;

/**
 * Return the minimum number of actions
 *
 * N: a non-negative integer representing the number of rows
 * M: another non-negative integer representing the number of columns
 * G: N x M array representing a grid
 */


bool solve(int N, int R, vector<int> &smokes) {
    int maxCap = R * 2;
    int amo = maxCap;
    int last = 1;
    for (int i = 0; i < smokes.size(); i++) {
        amo += smokes[i] - last;
        last = smokes[i];
        if (amo >= maxCap) amo = maxCap;
        amo -= R;
        if (amo < 0) {
            return false;
        }
    }
    return true;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) {
        int N, R;
        cin >> N >> R;
        vector<int> smokes(N);
        for (int j = 0; j < N; j++) {
            cin >> smokes[j];
        }
        if (solve(N, R, smokes)) {
            cout << "YES" << endl;
        } else cout << "NO" << endl;
    }
}
