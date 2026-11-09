#include <bits/stdc++.h>

using namespace std;

int formula(int P, int R, int C, int r, int c)
{
    int f = pow(P, 2) - (pow(r-R, 2) + pow(c-C, 2)) + 1;
    return f;
}

void brute_force()
{
    int N, M, Q; cin >> N >> M >> Q;
    vector<vector<int>> earthquakes(Q, vector<int>(3, -1));
    vector<vector<int>> grid(N, vector<int>(M, 0));
    for (int q = 0; q < Q; q ++)
    {
        cin >> earthquakes[q][0] >> earthquakes[q][1] >> earthquakes[q][2];
    }

    for (int q = 0; q < Q; q ++)
    {
        for (int i = 0; i < N; i ++)
        {
            for (int j = 0; j < M; j ++)
            {
                int f = formula(earthquakes[q][2], earthquakes[q][0], earthquakes[q][1], i, j);
                if (f > 0) grid[i][j] = f;
            }
        }
    }

    for (int i = 0; i < N; i ++)
    {
        for (int j = 0; j < M; j ++)
        {
            cout << grid[i][j];
            if (j == M-1) cout << endl; else cout << " ";
        }
    }
}




int main()
{
    int T; cin >> T;
    for (int t = 0; t < T; t ++)
    {
        brute_force();
    }


    return 0;
}