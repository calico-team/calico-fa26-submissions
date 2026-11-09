#include <iostream>
#include <vector>
using namespace std;

/**
 * Return the reading of every seismometer after all Q earthquakes have
 * occurred: an N by M grid of integers, where each reading is the shock
 * level of the most recent earthquake that reached that block (0 if no
 * earthquake reached it).
 *
 * N: the number of rows of blocks
 * M: the number of columns of blocks
 * Q: the number of earthquakes
 * X: the column of the epicenter of the i-th earthquake, in occurrence order
 * Y: the row of the epicenter of the i-th earthquake, in occurrence order
 * P: the power of the i-th earthquake, in occurrence order
 */
vector<vector<int>> solve(int N, int M, int Q, vector<int> &X, vector<int> &Y, vector<int> &P)
{
    // YOUR CODE HERE
    vector<vector<int>> values(N, std::vector<int>(M, 0));
    vector<int> parent(N * (M + 1), -1);

    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y <= M; y++)
        {
            parent[x * (M + 1) + y] = y;
        }
    }

    auto find = [&](int x, int y) -> int
    {
        int root = y;

        while (parent[x * (M + 1) + root] != root)
        {
            root = parent[x * (M + 1) + root];
        }

        while (parent[x * (M + 1) + y] != root)
        {
            int next = parent[x * (M + 1) + y];
            parent[x * (M + 1) + y] = root;
            y = next;
        }

        return root;
    };

    for (int i = Q - 1; i >= 0; i--)
    {
        int centerx = Y[i];
        int centery = X[i];

        int p = P[i];

        for (int r = centery - p; r <= centery + p; r++)
        {
            int dr = r - centery;
            int v = p * p - dr * dr;

            int w = (int)sqrt((double)v);

            while (w * w > v)
            {
                w--;
            }
            while ((w + 1) * (w + 1) <= v)
            {
                w++;
            }

            int low = centerx - w;
            int high = centerx + w;

            int c = find(r, low);
            while (c <= high)
            {
                int dc = c - centerx;
                values[r][c] = p * p - (dr * dr + dc * dc) + 1;
                parent[r * (M + 1) + c] = c + 1;
                c = find(r, c + 1);
            }
        }
    }

    return values;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--)
    {
        int N, M, Q;
        cin >> N >> M >> Q;
        vector<int> X(Q), Y(Q), P(Q);
        for (int i = 0; i < Q; i++)
        {
            cin >> X[i] >> Y[i] >> P[i];
        }
        vector<vector<int>> answer = solve(N, M, Q, X, Y, P);
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (j > 0)
                    std::cout << ' ';
                std::cout << answer[i][j];
            }
            std::cout << '\n';
        }
    }
    return 0;
}
