#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void run_case() {
    int row_cnt, col_cnt, q_cnt; if (!(cin >> row_cnt >> col_cnt >> q_cnt)) return;
    
    vector<string> mp(row_cnt);
    for(int i = 0; i < row_cnt; i++) {
        cin >> mp[i];
    }

    vector<vector<vector<int>>> cid(row_cnt, vector<vector<int>>(col_cnt, vector<int>(2, -1))); int total_comps = 0;
    
    int dr[] = {-1, 1, 0, 0}; int dc[] = {0, 0, -1, 1};
    
    for(int i = 0; i < row_cnt; i++) {
        for(int j = 0; j < col_cnt; j++) {
            for(int m = 0; m < 2; m++) {
                bool valid = false; if(mp[i][j] == '.') valid = true; else if(m == 0 && mp[i][j] == 'B') valid = true; else if(m == 1 && mp[i][j] == 'R') valid = true;
                
                if(valid && cid[i][j][m] == -1) {
                    queue<pair<pair<int, int>, int>> q; q.push({{i, j}, m}); cid[i][j][m] = total_comps;
                    
                    while(!q.empty()) {
                        auto curr = q.front(); q.pop(); int r = curr.first.first; int c = curr.first.second; int mode = curr.second;
                        
                        if(mp[r][c] == '.') {
                            int nm = 1 - mode;
                            if(cid[r][c][nm] == -1) {
                                cid[r][c][nm] = total_comps;
                                q.push({{r, c}, nm});
                            }
                        }
                        
                        for(int d = 0; d < 4; d++) {
                            int nr = r + dr[d]; int nc = c + dc[d];
                            if(nr >= 0 && nr < row_cnt && nc >= 0 && nc < col_cnt) {
                                char nt = mp[nr][nc];
                                bool ok = false; if(nt == '.') ok = true; else if(mode == 0 && nt == 'B') ok = true; else if(mode == 1 && nt == 'R') ok = true;
                                
                                if(ok && cid[nr][nc][mode] == -1) {
                                    cid[nr][nc][mode] = total_comps;
                                    q.push({{nr, nc}, mode});
                                }
                            }
                        }
                    }
                    total_comps++;
                }
            }
        }
    }
    
    for(int k = 0; k < q_cnt; k++) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2; bool possible = false; int start_comp = cid[r1][c1][0];
        if(start_comp != -1) {
            if(cid[r2][c2][0] == start_comp || cid[r2][c2][1] == start_comp) {
                possible = true;
            }
        }
        
        if(possible) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); int t;
    if(cin >> t) {
        while(t--) {
            run_case();
			       }
                  }
    
    return 0;
}