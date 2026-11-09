#include <bits/stdc++.h>
using namespace std;
void check(vector<vector<bool>> &possible, vector<vector<char>> &grid, int r, int c) {
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
        if (possible[options[i].first][options[i].second]) {
            continue;
        }
        possible[options[i].first][options[i].second] = true;
        check(possible, grid,options[i].first,options[i].second);
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
        
        vector<vector<bool>> possible(n);
        for (int i = 0; i < n; i++) {
            vector<bool> temp(m);
            possible[i] = temp;
        }
        possible[n-1][m-1] = true;
        check(possible, vec, n-1, m-1);

        for (int j = 0; j < q; j++) {
            int r; int c;
            cin >> r >> c;
            int bs;
            cin >> bs >> bs;
            if (possible[r][c]) {
                cout << "YES" << '\n';
            }
            else {
                cout << "NO" << '\n';
            }
        }
    }
}