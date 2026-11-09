#include <bits/stdc++.h>
using namespace std;
void check(vector<vector<int>> &possible, vector<vector<char>> &grid, int r, int c, int region) {
    vector<pair<int,int>> options = {pair<int,int>(r-1,c), pair<int,int>(r,c-1),pair<int,int>(r,c+1),pair<int,int>(r+1,c)};
    for (int i = 0; i < options.size(); i++) {
        if (options[i].first < 0 || options[i].first >= grid.size()) {
            continue;
        }
        if (options[i].second < 0 || options[i].second >= grid[0].size()) {
            continue;
        }
        if (grid[r][c] == 'R' && grid[options[i].first][options[i].second] == 'B') {
            continue;
        }
        if (grid[r][c] == 'B' && grid[options[i].first][options[i].second] == 'R') {
            continue;
        }
        if (possible[options[i].first][options[i].second] != -1) {
            continue;
        }
        possible[options[i].first][options[i].second] = region;
        check(possible, grid, options[i].first,options[i].second, region);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t; cin >> t;
    for (int tc = 0; tc < t; tc++) {
        int n, m, q; cin >> n >> m >> q;

        vector<vector<char>> vec(n);
        for (int i = 0; i < n; i++) {
            vector<char> tmp(m);
            for (int j = 0; j < m; j++) {
                char c; cin >> c;
                tmp[j] = c;
            }
            vec[i] = tmp;
        }
        
        vector<vector<int>> possible(n);
        for (int i = 0; i < n; i++) {
            vector<int> temp(m);
            for (int j = 0; j < m; j++) {
                temp[j] = -1;
            }
            possible[i] = temp;
        }
        bool condition = true;
        int region_count = 0;
        while(condition) {
            int coordx, coordy;
            bool found = false;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (possible[i][j] == -1) {
                        found = true;
                        coordy = i;
                        coordx = j;
                    }
                }
                if (found) {
                    break;
                }
            }
            if (!found) {
                break;
            }
            possible[coordy][coordx] = region_count;
            check(possible, vec, coordy, coordx, region_count);

            region_count++;
        }

        for (int j = 0; j < q; j++) {
            int r; int c;
            cin >> r >> c;
            int r2; int c2;
            cin >> r2 >> c2;
            if (possible[r][c] == possible[r2][c2]) {
                cout << "YES" << '\n';
            }
            else {
                cout << "NO" << '\n';
            }
        }
    }
}