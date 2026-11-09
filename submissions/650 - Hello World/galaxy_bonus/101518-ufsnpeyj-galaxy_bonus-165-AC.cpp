#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int main() {
    int t;
    cin >> t;
    // lets   setup directions firsst

    int dr[]={-1, 1, 0, 0};
    int dc[]={0, 0, -1, 1};



    while (t--) {
         int n, m, queries;
           cin >> n>>m>> queries;

         vector<string> grid(n);
             for (int i = 0; i<n;i++) cin >>grid[i];

            vector<vector<int>> group(n, vector<int>(m, -1));
            int id = 0;

        for (int i = 0; i < n; i++) {
             for (int j = 0; j < m; j++) {
                 if (group[i][j] != -1) continue;

                queue<pair<int, int>> q;
                q.push({i, j});
                group[i][j] = id;

                while (!q.empty()) {
                    int r = q.front().first;
                     int c = q.front().second;

                    q.pop();


                    for (int d = 0; d < 4; d++) {
                        int x = r + dr[d];

                        int y = c + dc[d];


                        if (x < 0 || x >= n || y < 0 || y >= m)
                            continue;
                         if (group[x][y] != -1)
                            continue;

                        char a = grid[r][c], b = grid[x][y];
                         if (a !='.' &&  b!='.'&& a!=b )
                            continue;
                        group[x][y] = id;

                        q.push({x, y});
                    }


                }
                id++;
            }

        }

        while (queries--) {
            int r1, c1, r2, c2;
            cin >>r1>>c1>>r2>>c2;

            if (group[r1][c1] ==group[r2][c2])
                cout<<"YES\n";
            else
                cout<<"NO\n";
        }
    }
    return 0; }