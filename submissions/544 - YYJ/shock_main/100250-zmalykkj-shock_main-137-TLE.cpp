#include <iostream>
#include <vector>
using namespace std;

/**
 * Return the reading of every seismometer after all Q earthquakes have
 * occurred: an N by M grid of integers, where each reading is the shock
 * level of the most recent earthquake that reached that block (0 if no
 * earthquake reached it).
 *
 * N: the number of rows of blocks
 * M: the number of columns of blocks
 * Q: the number of earthquakes
 * X: the column of the epicenter of the i-th earthquake, in occurrence order
 * Y: the row of the epicenter of the i-th earthquake, in occurrence order
 * P: the power of the i-th earthquake, in occurrence order
 */
vector<vector<int>> solve(int N, int M, int Q, vector<int>& X, vector<int>& Y, vector<int>& P) {
    vector<vector<int>> pow(N, vector<int>(M, 0));
    for(int i = 0; i < Q; i++){
        pair<int, int> c1 = {X[i] - P[i], Y[i] - P[i]};
        pair<int, int> c2 = {X[i] + P[i], Y[i] + P[i]};
        for(int x = c1.first; x <= c2.first; x++){
            for(int y = c1.second; y <= c2.second; y++){
                int npow = P[i] * P[i] - (x - X[i]) * (x - X[i]) - (y - Y[i]) * (y - Y[i]) + 1;
                if(npow > 0) pow[x][y] = npow;
            }
        }
    }

    return pow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<int> X(Q), Y(Q), P(Q);
        for (int i = 0; i < Q; i++) {
            cin >> X[i] >> Y[i] >> P[i];
        }
        vector<vector<int>> answer = solve(N, M, Q, X, Y, P);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (j > 0) cout << ' ';
                cout << answer[i][j];
            }
            cout << '\n';
        }
    }
    return 0;
}
