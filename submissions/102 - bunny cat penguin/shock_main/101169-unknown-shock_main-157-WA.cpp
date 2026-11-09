#include <iostream>
#include <vector>
#define FASTIO std::ios::sync_with_stdio(false); std::cin.tie(NULL); std::cout.tie(NULL)
using namespace std;

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, -1, 1};

bool isValid(int x, int y, int n, int m) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int main() {
    FASTIO;
    int T; cin >> T;
    while (T--) {
        int N, M, Q; cin >> N >> M >> Q;
        vector<vector<long long>> blocks(N, vector<long long>(M, 0));
        for (int i = 0; i < Q; i++) {
            int R, C, P; cin >> R >> C >> P;
            blocks[R][C] += (long long) P * P + 1;
            for (int r = 0; r < N; r++) {
                if ((long long) P * P - (long long) r * r + 1 <= 0) break;
                for (int c = 0; c < M; c++) {
                    if (r == 0 && c == 0) continue;

                    long long p = (long long) P * P - ((long long) r * r) - ((long long) c * c) + 1;
                    if (p <= 0) break;

                    if (r == 0) {
                        if (isValid(R, C + c, N, M)) blocks[R][C + c] += p;
                        if (isValid(R, C - c, N, M)) blocks[R][C - c] += p;
                        continue;
                    }
                    if (c == 0) {
                        if (isValid(R + r, C, N, M)) blocks[R + r][C] += p;
                        if (isValid(R - r, C, N, M)) blocks[R - r][C] += p;
                        continue;
                    }

                    for (int d = 0; d < 4; d++) {
                        int x = R + dx[d] * r;
                        int y = C + dy[d] * c;
                        if (isValid(x, y, N, M)) blocks[x][y] += p;
                    }
                }
            }
        }
        for (int r = 0; r < N; r++) {
            for (int c = 0; c < M; c++) {
                cout << blocks[r][c] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}