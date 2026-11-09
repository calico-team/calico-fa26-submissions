#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr int maxN = 201;
int N, Q, T, choices[4][2] = {
    {0, 1},
    {1, 0},
    {-1, 0},
    {0, -1}
};
char tiles[maxN][maxN];
bool visited[maxN][maxN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    for (int z = 0; z < T; z++)
    {
        int R, C; cin >> R >> C >> Q;
        memset(tiles, ' ', sizeof(tiles));
        memset(visited, false, sizeof(visited));

        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                cin >> tiles[i][j];
            }
        }

        queue<pair<int, int>> q;
        q.push({R - 1, C - 1});
        visited[R - 1][C - 1] = true;
        while (!q.empty())
        {
            auto [r, c] = q.front(); q.pop();
            for (auto a : choices)
            {
                int x = a[0], y = a[1];
                int newr = r + y, newc = x + c;
                if (newr >= 0 && newr < R && newc >= 0 && newc < C && (tiles[newr][newc] == tiles[r][c] || tiles[newr][newc] == '.' || tiles[r][c] == '.'))
                {
                    if (!visited[newr][newc])
                    {
                        visited[newr][newc] = true;
                        q.emplace(newr, newc);
                    }
                }
            }
        }
        for (int i = 0; i < Q; i++)
        {
            int rs, cs, re, ce; cin >> rs >> cs >> re >> ce;
            if (visited[rs][cs]) cout << "YES" << "\n";
            else cout << "NO" << "\n";
        }
    }
}