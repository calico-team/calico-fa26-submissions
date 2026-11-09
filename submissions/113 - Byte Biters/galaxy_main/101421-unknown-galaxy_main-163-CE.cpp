#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <algorithm>
#include <cmath>
#include <deque>
using namespace std;

vector<int> row_moves= {-1, 1, 0, 0};
vector<int> col_moves={0, 0, -1, 1};

bool standable(char c, int mode){
    if(c == '.'){
        return true;
    }
    if(mode==0){
        return c == 'B';
    }
    else{
        return c=='R';
    }
}
void painter(vector<vector<char>>& map, vector<vector<int>>& painted, int n, int m, int row, int col,int mode, int id){
    queue<pair<pair<int,int>,int>> q;
    q.push({{row,col},mode});
    painted[row][col] = id;
    while(!q.empty()){
        int r = q.front().first.first, c = q.front().first.second, cur_mode = q.front().second;
        q.pop();
        for(int i = 0; i < 4; ++i){
            int nr = r+ row_moves[i], nc = c +col_moves[i];
            if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                continue;
            }
            if(!standable(map[nr][nc],cur_mode)){
                continue;
            }
            if(painted[nr][nc]!=-1){
                continue;
            }
            painted[nr][nc] = id;
            q.push({{nr,nc},cur_mode});
        }
        if(map[r][c]=='.'){
            int other = 1 - cur_mode;
            for(int i = 0; i < 4; ++i){
                int nr = r+ row_moves[i], nc = c +col_moves[i];
                if(nr < 0 || nc < 0 || nr >= n || nc >= m){
                    continue;
                }
                if(!standable(map[nr][nc],other)){
                    continue;
                }
                if(painted[nr][nc]!=-1){
                    continue;
                }
                painted[nr][nc] = id;
                q.push({{nr,nc},other});
            }
        }
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t; cin >> t;
    while(t--){
        int n,m,q; cin >> n >> m >> q;
        vector<vector<char>> map(n,vector<char>(m));
        vector<pair<int,int>> regular_tile_locs;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                char c; cin >> c;
                if(c == '.'){
                    regular_tile_locs.push_back({i,j});
                }
                map[i][j] = c;
            }
        }
        vector<vector<int>> painted(n,vector<int>(m,-1));
        int id = 0;
        for(int i = 0; i < n ; i++){
            for(int j = 0; j < m; j++){
                if(painted[i][j]!= -1) continue;
                int mode = 0;
                if(map[i][j] == 'R'){
                    mode = 1;
                } else if(map[i][j] != '.' && map[i][j]!='B'){
                    continue;
                }
                painter(map,painted,n,m,i,j,mode,id);
                id++;
            }
        }
        while(q--){
            int start_row, start_col, end_row,end_col; cin >> start_row >> start_col >> end_row >> end_col;
            if (painted[start_row][start_col] == painted[end_row][end_col]){
                cout << "YES" << endl;
            } else{
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}