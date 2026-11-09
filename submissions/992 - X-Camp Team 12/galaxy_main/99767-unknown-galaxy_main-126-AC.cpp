#include <bits/stdc++.h>
using namespace std;

int t;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> t;
    while(t--){
        int n, m, q;
        cin >> n >> m >> q;
        int a[250][250];
        int c[250][250];

        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                char tmp;
                cin >> tmp;
                if (tmp == '.') a[i][j] = 0;
                else if (tmp == 'R') a[i][j] = 1;
                else a[i][j] = 2;
                c[i][j] = -1;
            }
        }
        int tmp = 0;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < m; j++){
                if (c[i][j] != -1) continue;
                queue<pair<int, int> > q;
                q.push(make_pair(i, j));
                c[i][j] = tmp;
                while (!q.empty()){
                    int nx = q.front().first;
                    int ny = q.front().second;
                    q.pop();
                    if (a[nx][ny] == 0){
                        for (int k = 0; k < 4; k++){
                            int tx = nx + dx[k];
                            int ty = ny + dy[k];
                            if (tx >= 0 && ty >= 0 && tx < n && ty < m && c[tx][ty] == -1){
                                c[tx][ty] = tmp;
                                q.push(make_pair(tx, ty));
                            }
                        }
                    }
                    else if (a[nx][ny] == 1){
                        for (int k = 0; k < 4; k++){
                            int tx = nx + dx[k];
                            int ty = ny + dy[k];
                            if (tx >= 0 && ty >= 0 && tx < n && ty < m && c[tx][ty] == -1 && a[tx][ty] != 2){
                                c[tx][ty] = tmp;
                                q.push(make_pair(tx, ty));
                            }
                        }
                    }
                    else if (a[nx][ny] == 2){
                        for (int k = 0; k < 4; k++){
                            int tx = nx + dx[k];
                            int ty = ny + dy[k];
                            if (tx >= 0 && ty >= 0 && tx < n && ty < m && c[tx][ty] == -1 && a[tx][ty] != 1){
                                c[tx][ty] = tmp;
                                q.push(make_pair(tx, ty));
                            }
                        }
                    }
                }
                tmp++;
            }
        }
        for (int i = 1; i <= q; i++){
            int x, y, s, e;
            cin >> x >> y >> s >> e;
            if (c[x][y] == c[s][e]) cout << "YES" << endl;
            else cout << "NO" << endl;
        }
    }
}
