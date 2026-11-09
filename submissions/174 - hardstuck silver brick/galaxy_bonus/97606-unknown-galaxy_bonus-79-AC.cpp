#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int dr[] = {-1,1,0,0};
const int dc[] = {0,0,-1,1};

struct St {
    int r, c, m;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int T;
    cin >> T;
    while (T--) {
        int N, M, Q;
        cin >> N >> M >> Q;
        
        vector<string> g(N);
        for (int i=0;i<N;i++) {
            cin >> g[i];
        }
        
        vector<vector<vector<int>>> comp(N, vector<vector<int>>(M, vector<int>(2, -1)));
        int cc = 0;
        for (int i=0;i<N;i++) {
            for (int j=0;j<M;j++) {
                for (int m=0;m<2;m++) {
                    bool ctv = false;
                    if (m == 0) {
                        if (g[i][j] == 'B' || g[i][j] == '.') {ctv = true;}
                    } else {
                        if (g[i][j] == 'R' || g[i][j] == '.') {ctv = true;}
                    }
                    
                    if (ctv && comp[i][j][m] == -1) {
                        queue<St> q;
                        comp[i][j][m] = cc;
                        q.push({i,j,m});
                        
                        while (!q.empty()) {
                            St cur = q.front();
                            q.pop();
                            
                            for (int d=0;d<4;d++) {
                                int nr = cur.r + dr[d];
                                int nc = cur.c + dc[d];
                                
                                if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                                    bool ntv = false;
                                    if (cur.m == 0) {
                                        if (g[nr][nc] == 'B' || g[nr][nc] == '.') {ntv = true;}
                                    } else {
                                        if (g[nr][nc] == 'R' || g[nr][nc] == '.') {ntv = true;}
                                    }
                                    
                                    if (ntv && comp[nr][nc][cur.m] == -1) {
                                        comp[nr][nc][cur.m] = cc;
                                        q.push({nr,nc,cur.m});
                                    }
                                }
                            }
                            if (g[cur.r][cur.c] == '.') {
                                int nm = 1 - cur.m;
                                if (comp[cur.r][cur.c][nm] == -1) {
                                    comp[cur.r][cur.c][nm] = cc;
                                    q.push({cur.r,cur.c,nm});
                                }
                            }
                        }
                        cc++;
                    }
                }
            }
        }
        for (int i=0;i<Q;i++) {
            int rs, cs, re, ce;
            cin >> rs >> cs >> re >> ce;
            
            int sc = comp[rs][cs][0]; 
            bool ok = false;
            
            bool dbv = (g[re][ce] == 'B' || g[re][ce] == '.');
            if (dbv && comp[re][ce][0] == sc) {
                ok = true;
            }
            
            bool drv = (g[re][ce] == 'R' || g[re][ce] == '.');
            if (drv && comp[re][ce][1] == sc) {
                ok = true;
            }
            
            if (ok) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
}