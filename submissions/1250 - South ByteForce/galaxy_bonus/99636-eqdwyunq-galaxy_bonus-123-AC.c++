#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int T;
    cin>> T;

    while (T--) {
        int n, m, q;
        cin>> n>> m>> q;

        vector<string> g(n);
        for (int i=0; i< n; i++) cin>> g[i];

        vector<int> comp(n*m*2, -1);
        int compCount= 0;

        int dir_row[4]= {1, -1, 0, 0};
        int dir_col[4]= {0, 0, 1, -1};

        for (int r= 0; r< n; r++) {
            for (int c= 0; c< m; c++) {
                for (int mode= 0; mode< 2; mode++) {
                    char charac= g[r][c];
                    bool valid= (charac== '.') || (charac== 'B' && mode== 0) || (charac== 'R' && mode== 1);
                    int id = (r* m+c)*2 + mode;
                    if (!valid || comp[id]!= -1) continue;

                    queue<int> bfs;
                    bfs.push(id);
                    comp[id]= compCount;
                    while (!bfs.empty()) {
                        int current= bfs.front();
                        bfs.pop();
                        int currmode= current%2;
                        int cell= current/2;
                        int curr_row=cell/m;
                        int curr_col=cell%m;

                        for (int dir = 0; dir< 4; dir++) {
                            int new_row = curr_row + dir_row[dir];
                            int new_col = curr_col + dir_col[dir];
                            if (new_row < 0 || new_row >= n || new_col < 0 || new_col >= m) continue;
                            char neighbor_char = g[new_row][new_col];
                            bool ok = (neighbor_char == '.') || (neighbor_char == 'B' && currmode == 0) || (neighbor_char == 'R' && currmode == 1);
                            int neighbor_id = (new_row * m + new_col) * 2 + currmode;
                            if (ok && comp[neighbor_id] == -1) {
                                comp[neighbor_id] = compCount;
                                bfs.push(neighbor_id);
                            }
                        }

                        if (g[curr_row][curr_col] == '.') {
                            int neighbor_id = cell * 2 + (1 - currmode);
                            if (comp[neighbor_id] == -1) {
                                comp[neighbor_id] = compCount;
                                bfs.push(neighbor_id);
                            }
                        }
                    }
                    compCount++;
                }
            }
        }

        for (int i = 0; i < q; i++) {
            int row_qstart, col_qstart, row_qend,col_qend;
            cin >> row_qstart >> col_qstart >> row_qend>>col_qend;
            int start = comp[(row_qstart * m + col_qstart) * 2 + 0];
            int e0 = comp[(row_qend* m +col_qend) * 2 + 0];
            int e1 = comp[(row_qend* m +col_qend) * 2 + 1];
            if (start != -1 && (e0 ==start || e1 ==start)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
    }
}