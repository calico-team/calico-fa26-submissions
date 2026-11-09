#include <bits/stdc++.h>
#define int long long
using namespace std;

struct bfs
{
    int n;
    int m;
    int mode; // 0 -> blue; 1 -> red
};

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        int n, m, q;
        cin >> n >> m >> q;
        vector<string> grid(n);
        for (int i = 0; i < n; i++)
        {
            string c;
            cin >> c;
            grid[i] = c;
        }
        vector<vector<vector<int>>> isPossible(n, vector<vector<int>>(m, vector<int>(2, -1))); // assume it is NOT possible unless proven otherwise
        // -1 && 0 -> not visited
        // 1 -> possible

        int init_n = n - 1, init_m = m - 1;
        queue<bfs> queue;
        bfs sblue = {init_n, init_m, 0}; // start from blue
        bfs sred = {init_n, init_m, 1};  // start from red
        queue.push(sblue);
        queue.push(sred);
        while (!queue.empty())
        {
            auto current = queue.front();
            queue.pop();
            if ((current.mode == 0 && grid[current.n][current.m] == 'R') || (current.mode == 1 && grid[current.n][current.m] == 'B') || (isPossible[current.n][current.m][current.mode] == 1))
            {
                continue; // skip if the mode is wrong
            }
            isPossible[current.n][current.m][current.mode] = 1;

            if (grid[current.n][current.m] == '.' && isPossible[current.n][current.m][1 - current.mode] == -1)
            {
                current.mode = 1 - current.mode;
                queue.push(current);
                current.mode = 1 - current.mode;
            }

            // adjacent cells are up, down, left, and right
            // Go Up
            if (current.n - 1 >= 0)
            {
                current.n -= 1;
                if (isPossible[current.n][current.m][current.mode] == -1)
                    queue.push(current);
                current.n += 1;
            }
            // Go Down
            if (current.n + 1 < n)
            {
                current.n += 1;
                if (isPossible[current.n][current.m][current.mode] == -1)
                    queue.push(current);
                current.n -= 1;
            }

            // Go Right
            if (current.m + 1 < m)
            {
                current.m += 1;
                if (isPossible[current.n][current.m][current.mode] == -1)
                    queue.push(current);
                current.m -= 1;
            }

            // Go Left
            if (current.m - 1 >= 0)
            {
                current.m -= 1;
                if (isPossible[current.n][current.m][current.mode] == -1)
                    queue.push(current);
                current.m += 1;
            }
        }
        while (q--)
        {
            int nn, mm, a, b;
            cin >> nn >> mm >> a >> b;
            if (isPossible[nn][mm][0] == 1)
            {
                cout << "YES\n";
            }
            else
            {
                cout << "NO\n";
            }
        }
    }
}