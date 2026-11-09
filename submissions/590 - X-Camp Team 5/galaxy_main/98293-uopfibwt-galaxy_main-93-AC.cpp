#include <bits/stdc++.h>

using namespace std;

class DisjointSets
{
private:
    vector<int> parents;
    vector<int> sizes;

public:
    DisjointSets(int size) : parents(size), sizes(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parents[i] = i;
        }
    }

    /** @return the "representative" node in x's component */
    int find(int x) { return parents[x] == x ? x : (parents[x] = find(parents[x])); }

    /** @return whether the merge changed connectivity */
    bool unite(int x, int y)
    {
        int x_root = find(x);
        int y_root = find(y);
        if (x_root == y_root)
        {
            return false;
        }

        if (sizes[x_root] < sizes[y_root])
        {
            swap(x_root, y_root);
        }
        sizes[x_root] += sizes[y_root];
        parents[y_root] = x_root;
        return true;
    }

    /** @return whether x and y are in the same connected component */
    bool connected(int x, int y) { return find(x) == find(y); }
};

/**
 * Return an array of Q strings, the i-th of which is "YES"
 * if Big Ben can travel from start[i] to end[i], and "NO"
 * otherwise.
 *
 * N: the number of rows in the grid
 * M: the number of columns in the grid
 * Q: the number of queries
 * G: the grid, where each tile is 'R', 'B', or '.'
 * start: the (row, column) of the starting tile of each query
 * end: the (row, column) of the ending tile of each query
 */

int toNum(int i, int j, int N, int M)
{
    return i * M + j;
}
int dx[] = {1, 0, 0, -1};
int dy[] = {0, 1, -1, 0};
vector<string> solve(int N, int M, int Q, vector<string> &G, vector<pair<int, int>> &start, vector<pair<int, int>> &end)
{
    DisjointSets DSU(N * M);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {

            for (int k = 0; k < 4; k++)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && nj >= 0 && ni < N && nj < M)
                {
                    if (G[i][j] == '.')
                    {
                        DSU.unite(toNum(i, j, N, M), toNum(ni, nj, N, M));
                    }
                    else if (G[i][j] == G[ni][nj])
                    {
                        DSU.unite(toNum(i, j, N, M), toNum(ni, nj, N, M));
                    }
                }
            }
        }
    }
    vector<string> output = {};
    for (int i = 0; i < Q; i++)
    {
        pair<int, int> startpi = start[i];
        pair<int, int> endpi = end[i];
        int n1 = toNum(startpi.first, startpi.second, N, M);
        int n2 = toNum(endpi.first, endpi.second, N, M);
        bool ans = DSU.connected(n1, n2);
        if (ans)
        {
            output.push_back("YES");
        }
        else
        {
            output.push_back("NO");
        }
    }
    return output;
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<string> G(N);
        for (int j = 0; j < N; j++)
        {
            cin >> G[j];
        }
        vector<pair<int, int>> start, end;
        for (int j = 0; j < Q; j++)
        {
            int start_row, start_col, end_row, end_col;
            cin >> start_row >> start_col >> end_row >> end_col;
            start.push_back({start_row, start_col});
            end.push_back({end_row, end_col});
        }

        for (string s : solve(N, M, Q, G, start, end))
        {
            cout << s << '\n';
        }
    }
}
