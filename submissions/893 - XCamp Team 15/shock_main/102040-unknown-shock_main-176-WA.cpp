#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
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
    vector<vector<int>> seismometers(N, vector<int>(M, 0));
    for (int earthquake = 0; earthquake < Q; earthquake++) {
        pair<int, int> epicenter = {Y[earthquake], X[earthquake]};
        int power = P[earthquake];
        vector<vector<bool>> visited(M, vector<bool>(N, false));

        queue<pair<int, int>> toProcess;
        toProcess.push(epicenter);
        visited[epicenter.second][epicenter.first] = true;

        while (!toProcess.empty()) {
            int currentRow = toProcess.front().first;
            int currentCol = toProcess.front().second;
            toProcess.pop();
            int currentPower = (power * power) - ((currentRow - epicenter.first)*(currentRow - epicenter.first) + (currentCol - epicenter.second)*(currentCol - epicenter.second)) + 1;
            if (currentPower <= 0) {
                continue;
            }
            seismometers[currentCol][currentRow] = currentPower;
            for (int rowIncrease = -1; rowIncrease <= 1; rowIncrease ++) {
                for (int colIncrease = -1; colIncrease <= 1; colIncrease ++) {
                    if (rowIncrease == 0 && colIncrease == 0) {
                        continue;
                    }
                    int newRow = currentRow + rowIncrease;
                    int newCol = currentCol + colIncrease;
                    if (
                        newRow >= 0 && newRow < N && 
                        newCol >= 0 && newCol < M &&
                        !visited[newCol][newRow]
                    ){
                        toProcess.push(make_pair(newRow, newCol));
                        visited[newCol][newRow] = true;
                    }
                }
            }
        }
    }

    return seismometers;
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
