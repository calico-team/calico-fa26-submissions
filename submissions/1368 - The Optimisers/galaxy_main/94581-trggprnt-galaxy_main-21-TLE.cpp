#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define all(a) a.begin(), a.end()
#define sz(a) int(a.size())
#define fastio ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)

const int dY[4] = {1, -1, 0, 0};
const int dX[4] = {0, 0, 1, -1};

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> grid(n, vector<int>(m));
    for(auto &row : grid)
    {
        for(auto &col : row)
        {
            char c;
            cin >> c;
            if(c == 'R') col = 0;
            else if(c == '.') col = 1;
            else if(c == 'B') col = 2;
        }
    }

    while(q--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        queue<pair<int, int>> q;
        vector<vector<bool>> vist(n, vector<bool>(m, false));
        q.push({a, b});
        vist[a][b] = true;

        while(!q.empty())
        {
            auto act = q.front();
            q.pop();

            for(int i = 0; i < 4; i++)
            {
                int ny = act.first + dY[i];
                int nx = act.second + dX[i];

                if(ny < 0 || ny >= n || nx < 0 || nx >= m) continue;
                if(vist[ny][nx]) continue;
                if(abs(grid[act.first][act.second] - grid[ny][nx]) > 1) continue;
                q.push({ny, nx});
                vist[ny][nx] = true;
            }
        }
        cout << (vist[c][d] ? "YES\n" : "NO\n");
    }
}

int main()
{
    int t;
    cin >> t;
    while(t--) solve();
    return 0;
}